#include <iostream>

#include <random>
#include <string>
#include <chrono>
#include "DiskManager.h"
#include "Allocator.h"
#include "defs.h"
#include "DB.h"

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

int main () {
    auto start = high_resolution_clock::now();
    DB *db = new DB("test.db");

    create(db);
    test(db);

    //fetch(db, 100000021);

    db->shutdown();


    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    std::cout << "OVERALL RUNTIME: "<< duration.count() << std::endl;
    return 0;
}
