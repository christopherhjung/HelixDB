#include <iostream>

#include <random>
#include <string>
#include <chrono>
#include "DiskManager.h"
#include "Allocator.h"
#include "defs.h"
#include "DB.h"

#include "antlr4-runtime.h"
#include "TLexer.h"
#include "TParser.h"
#include "TParserVisitor.h"

using namespace std::chrono;


int setProp = 0;
int createInstance = 0;

void test(DB *db){
    std::default_random_engine dev(0);
    std::uniform_int_distribution<int> dist(1, 99999999);
    std::uniform_int_distribution<int> dist2(1, 32563242);

    debugCounter = &createInstance;
    u64 startInstance = 0;
    int size = 1000000;

    auto start = high_resolution_clock::now();

    u32 classId = db->findName("User");
    u32 propertyId = db->findName("amount");
    u32 hashId = db->findName("hash");
    for(int i = 0 ; i < size ; i++){
        u32 number = dist(dev);

        u64 instance = db->createInstance(classId);

        if(i == 0){
            startInstance = instance;
        }

        debugCounter = &setProp;
        db->setPropertyValue(instance, propertyId, &number);

        u32 number2 = dist2(dev);
        db->setPropertyValue(instance, hashId, &number2);

        debugCounter = &createInstance;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    std::cout << "MILLIS: "<< duration.count() << std::endl;

    std::cout << "setProp:" << setProp << std::endl;
    std::cout << "createInstance:" << createInstance << std::endl;

    dev.seed(0);

    for(int i = 0 ; i < size ; i++){
        u32 number = dist(dev);

        u64 instanceClassified = db->classify(i + startInstance, "User");
        u32 value = 0;
        db->getPropertyValue(instanceClassified, "amount", &value);
        check(value == number, "Test fehler at index:" + std::to_string(i) + " " + std::to_string(value) + " != " +
                               std::to_string(number));

        value = 0;
        db->getPropertyValue(instanceClassified, "hash", &value);

        u32 number2 = dist2(dev);
        check(value == number2, "Test fehler at index:" + std::to_string(i) + " " + std::to_string(value) + " != " +
                                std::to_string(number2));
    }

    PropertyEntry propertyEntry = db->getProperty("User", "amount");
    std::cout << "offset:" << startInstance + size << std::endl;
    std::cout << propertyEntry.byteWidth << std::endl;

    std::cout << "Page count:" << db->getPageCount() << std::endl;
    std::cout << "Size:" << db->getSize() << std::endl;
}

void create(DB *db){
    if(!db->exists("User")){
        db->createClass("User");
        db->createProperty("User", "amount", 4);
        db->createProperty("User", "hash", 4);
    }
}

void fetch(DB *db, u32 index){
    u32 value = 0;
    u64 instance = DB::classify(index, db->findName("User"));
    db->getPropertyValue(instance, "amount", &value);

    std::cout << "Value:" << value << std::endl;
}


using namespace antlrcpptest;

void runStatement(TParser::StatementContext *statement, DB* db){
    if(TParser::InsertContext *insertContext = statement->insert()){
        TParser::ClassDefinitionContext *classDefinitionContext = insertContext->type;

        std::string className = classDefinitionContext->getText();
        std::vector<TParser::PairContext*> pairs = insertContext->pair();


        i32 classId = db->findName(className, false);

        if(classId == -1){
            printf("Class %s not found\n", className.c_str());
            return;
        }

        u64 instanceId = db->createInstance(classId);

        printf("Instance %lu created from Class %s\n", instanceId, className.c_str());

        for( TParser::PairContext* pair : pairs ){
            std::string propertyName = pair->name->getText();
            u32 value = std::stoi(pair->value->getText());

            u32 propertyId = db->findName(propertyName);

            if(propertyId == -1){
                printf("Property %s of Class %s not found\n", propertyName.c_str(), className.c_str());
                continue;
            }

            db->setPropertyValue(instanceId, propertyId, &value);

            printf("Value %d added to Property %s of instance %lu\n", value, propertyName.c_str(), instanceId);
        }
    }else if(TParser::SelectContext *selectContext = statement->select()){
        std::string className = selectContext->type->getText();
        //std::string selectContext->name->getText();

        u32 classId = db->findName(className);
        u32 index = std::stoi(selectContext->id->getText());

        u64 instance = DB::classify(index, classId);

        TParser::ExprContext *expression = selectContext->expression;

        //expression->variable
        std::string propertyName = expression->property->getText();

        u32 value;
        db->getPropertyValue(instance, propertyName, &value);
        printf("Property value of %s is %d\n", propertyName.c_str(), value);
    }else if(TParser::CreateClassContext *createClassContext = statement->createClass()){
        std::string className = createClassContext->name->getText();
        db->createClass(className);
        printf("Created Class %s\n", className.c_str());
    }else if(TParser::CreatePropertyContext *createProperty = statement->createProperty()){
        std::string propertyName = createProperty->name->getText();
        std::string className = createProperty->type->getText();

        db->createProperty(className, propertyName, 4);
        printf("Created Property %s.%s\n", className.c_str(), propertyName.c_str());
    }
}

int main () {
    auto start = high_resolution_clock::now();
    DB *db = new DB("test.db");

    create(db);
    //test(db);

    //fetch(db, 100000021);

   // std::ifstream file("code.kb");


    std::string line;

    while(true){
        std::getline(std::cin, line);

        if(line == "exit"){
            break;
        }

        antlr4::ANTLRInputStream input(line);
        TLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        TParser parser(&tokens);

        TParser::MainContext *main = parser.main();

        if(main->EOF() != nullptr){
            runStatement(main->statement(), db);
        }
    }

    db->shutdown();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    std::cout << "OVERALL RUNTIME: "<< duration.count() << std::endl;
    return 0;
}
