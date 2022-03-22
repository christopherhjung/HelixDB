// Generated from /Users/chris/CLionProjects/HelixDB/grammar/TLexer.g4 by ANTLR 4.9.2
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class TLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.9.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		DelimitedComment=1, LineComment=2, WS=3, NL=4, Select=5, From=6, Insert=7, 
		Create=8, Class=9, Property=10, Where=11, OpenBracket=12, CloseBracket=13, 
		OpenParenthesis=14, CloseParenthesis=15, OpenBrace=16, CloseBrace=17, 
		Comma=18, Dot=19, Colon=20, Equals=21, NotEquals=22, Plus=23, Minus=24, 
		Div=25, Mod=26, Star=27, LogicalOr=28, LogicalAnd=29, Less=30, Greater=31, 
		LessEquals=32, GreaterEquals=33, Identifier=34, Number=35;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"DelimitedComment", "LineComment", "WS", "NL", "Select", "From", "Insert", 
			"Create", "Class", "Property", "Where", "OpenBracket", "CloseBracket", 
			"OpenParenthesis", "CloseParenthesis", "OpenBrace", "CloseBrace", "Comma", 
			"Dot", "Colon", "Equals", "NotEquals", "Plus", "Minus", "Div", "Mod", 
			"Star", "LogicalOr", "LogicalAnd", "Less", "Greater", "LessEquals", "GreaterEquals", 
			"Identifier", "Number"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, null, null, null, null, "'select'", "'from'", "'insert'", "'create'", 
			"'class'", "'property'", "'where'", "'['", "']'", "'('", "')'", "'{'", 
			"'}'", "','", "'.'", "':'", "'='", "'!='", "'+'", "'-'", "'/'", "'%'", 
			"'*'", "'||'", "'&&'", "'<'", "'>'", "'<='", "'>='"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "DelimitedComment", "LineComment", "WS", "NL", "Select", "From", 
			"Insert", "Create", "Class", "Property", "Where", "OpenBracket", "CloseBracket", 
			"OpenParenthesis", "CloseParenthesis", "OpenBrace", "CloseBrace", "Comma", 
			"Dot", "Colon", "Equals", "NotEquals", "Plus", "Minus", "Div", "Mod", 
			"Star", "LogicalOr", "LogicalAnd", "Less", "Greater", "LessEquals", "GreaterEquals", 
			"Identifier", "Number"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public TLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "TLexer.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2%\u00da\b\1\4\2\t"+
		"\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\3\2\3\2\3\2\3\2\3\2\7\2O\n\2\f\2\16\2R\13\2\3"+
		"\2\3\2\3\2\3\2\3\2\3\3\3\3\3\3\3\3\7\3]\n\3\f\3\16\3`\13\3\3\3\3\3\3\4"+
		"\3\4\3\4\3\4\3\5\3\5\3\5\5\5k\n\5\3\5\3\5\3\6\3\6\3\6\3\6\3\6\3\6\3\6"+
		"\3\7\3\7\3\7\3\7\3\7\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\t\3\t\3\t\3\t\3\t\3"+
		"\t\3\t\3\n\3\n\3\n\3\n\3\n\3\n\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13"+
		"\3\13\3\f\3\f\3\f\3\f\3\f\3\f\3\r\3\r\3\16\3\16\3\17\3\17\3\20\3\20\3"+
		"\21\3\21\3\22\3\22\3\23\3\23\3\24\3\24\3\25\3\25\3\26\3\26\3\27\3\27\3"+
		"\27\3\30\3\30\3\31\3\31\3\32\3\32\3\33\3\33\3\34\3\34\3\35\3\35\3\35\3"+
		"\36\3\36\3\36\3\37\3\37\3 \3 \3!\3!\3!\3\"\3\"\3\"\3#\3#\7#\u00d1\n#\f"+
		"#\16#\u00d4\13#\3$\6$\u00d7\n$\r$\16$\u00d8\3P\2%\3\3\5\4\7\5\t\6\13\7"+
		"\r\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35\20\37\21!\22#\23%\24\'\25"+
		")\26+\27-\30/\31\61\32\63\33\65\34\67\359\36;\37= ?!A\"C#E$G%\3\2\7\4"+
		"\2\f\f\17\17\5\2\13\13\16\16\"\"\4\2C\\c|\5\2C\\aac|\3\2\62;\2\u00df\2"+
		"\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2"+
		"\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2"+
		"\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2"+
		"\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2"+
		"\2\61\3\2\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67\3\2\2\2\29\3\2\2\2\2;\3\2"+
		"\2\2\2=\3\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2C\3\2\2\2\2E\3\2\2\2\2G\3\2\2\2"+
		"\3I\3\2\2\2\5X\3\2\2\2\7c\3\2\2\2\tj\3\2\2\2\13n\3\2\2\2\ru\3\2\2\2\17"+
		"z\3\2\2\2\21\u0081\3\2\2\2\23\u0088\3\2\2\2\25\u008e\3\2\2\2\27\u0097"+
		"\3\2\2\2\31\u009d\3\2\2\2\33\u009f\3\2\2\2\35\u00a1\3\2\2\2\37\u00a3\3"+
		"\2\2\2!\u00a5\3\2\2\2#\u00a7\3\2\2\2%\u00a9\3\2\2\2\'\u00ab\3\2\2\2)\u00ad"+
		"\3\2\2\2+\u00af\3\2\2\2-\u00b1\3\2\2\2/\u00b4\3\2\2\2\61\u00b6\3\2\2\2"+
		"\63\u00b8\3\2\2\2\65\u00ba\3\2\2\2\67\u00bc\3\2\2\29\u00be\3\2\2\2;\u00c1"+
		"\3\2\2\2=\u00c4\3\2\2\2?\u00c6\3\2\2\2A\u00c8\3\2\2\2C\u00cb\3\2\2\2E"+
		"\u00ce\3\2\2\2G\u00d6\3\2\2\2IJ\7\61\2\2JK\7,\2\2KP\3\2\2\2LO\5\3\2\2"+
		"MO\13\2\2\2NL\3\2\2\2NM\3\2\2\2OR\3\2\2\2PQ\3\2\2\2PN\3\2\2\2QS\3\2\2"+
		"\2RP\3\2\2\2ST\7,\2\2TU\7\61\2\2UV\3\2\2\2VW\b\2\2\2W\4\3\2\2\2XY\7\61"+
		"\2\2YZ\7\61\2\2Z^\3\2\2\2[]\n\2\2\2\\[\3\2\2\2]`\3\2\2\2^\\\3\2\2\2^_"+
		"\3\2\2\2_a\3\2\2\2`^\3\2\2\2ab\b\3\2\2b\6\3\2\2\2cd\t\3\2\2de\3\2\2\2"+
		"ef\b\4\3\2f\b\3\2\2\2gk\7\f\2\2hi\7\17\2\2ik\7\f\2\2jg\3\2\2\2jh\3\2\2"+
		"\2kl\3\2\2\2lm\b\5\3\2m\n\3\2\2\2no\7u\2\2op\7g\2\2pq\7n\2\2qr\7g\2\2"+
		"rs\7e\2\2st\7v\2\2t\f\3\2\2\2uv\7h\2\2vw\7t\2\2wx\7q\2\2xy\7o\2\2y\16"+
		"\3\2\2\2z{\7k\2\2{|\7p\2\2|}\7u\2\2}~\7g\2\2~\177\7t\2\2\177\u0080\7v"+
		"\2\2\u0080\20\3\2\2\2\u0081\u0082\7e\2\2\u0082\u0083\7t\2\2\u0083\u0084"+
		"\7g\2\2\u0084\u0085\7c\2\2\u0085\u0086\7v\2\2\u0086\u0087\7g\2\2\u0087"+
		"\22\3\2\2\2\u0088\u0089\7e\2\2\u0089\u008a\7n\2\2\u008a\u008b\7c\2\2\u008b"+
		"\u008c\7u\2\2\u008c\u008d\7u\2\2\u008d\24\3\2\2\2\u008e\u008f\7r\2\2\u008f"+
		"\u0090\7t\2\2\u0090\u0091\7q\2\2\u0091\u0092\7r\2\2\u0092\u0093\7g\2\2"+
		"\u0093\u0094\7t\2\2\u0094\u0095\7v\2\2\u0095\u0096\7{\2\2\u0096\26\3\2"+
		"\2\2\u0097\u0098\7y\2\2\u0098\u0099\7j\2\2\u0099\u009a\7g\2\2\u009a\u009b"+
		"\7t\2\2\u009b\u009c\7g\2\2\u009c\30\3\2\2\2\u009d\u009e\7]\2\2\u009e\32"+
		"\3\2\2\2\u009f\u00a0\7_\2\2\u00a0\34\3\2\2\2\u00a1\u00a2\7*\2\2\u00a2"+
		"\36\3\2\2\2\u00a3\u00a4\7+\2\2\u00a4 \3\2\2\2\u00a5\u00a6\7}\2\2\u00a6"+
		"\"\3\2\2\2\u00a7\u00a8\7\177\2\2\u00a8$\3\2\2\2\u00a9\u00aa\7.\2\2\u00aa"+
		"&\3\2\2\2\u00ab\u00ac\7\60\2\2\u00ac(\3\2\2\2\u00ad\u00ae\7<\2\2\u00ae"+
		"*\3\2\2\2\u00af\u00b0\7?\2\2\u00b0,\3\2\2\2\u00b1\u00b2\7#\2\2\u00b2\u00b3"+
		"\7?\2\2\u00b3.\3\2\2\2\u00b4\u00b5\7-\2\2\u00b5\60\3\2\2\2\u00b6\u00b7"+
		"\7/\2\2\u00b7\62\3\2\2\2\u00b8\u00b9\7\61\2\2\u00b9\64\3\2\2\2\u00ba\u00bb"+
		"\7\'\2\2\u00bb\66\3\2\2\2\u00bc\u00bd\7,\2\2\u00bd8\3\2\2\2\u00be\u00bf"+
		"\7~\2\2\u00bf\u00c0\7~\2\2\u00c0:\3\2\2\2\u00c1\u00c2\7(\2\2\u00c2\u00c3"+
		"\7(\2\2\u00c3<\3\2\2\2\u00c4\u00c5\7>\2\2\u00c5>\3\2\2\2\u00c6\u00c7\7"+
		"@\2\2\u00c7@\3\2\2\2\u00c8\u00c9\7>\2\2\u00c9\u00ca\7?\2\2\u00caB\3\2"+
		"\2\2\u00cb\u00cc\7@\2\2\u00cc\u00cd\7?\2\2\u00cdD\3\2\2\2\u00ce\u00d2"+
		"\t\4\2\2\u00cf\u00d1\t\5\2\2\u00d0\u00cf\3\2\2\2\u00d1\u00d4\3\2\2\2\u00d2"+
		"\u00d0\3\2\2\2\u00d2\u00d3\3\2\2\2\u00d3F\3\2\2\2\u00d4\u00d2\3\2\2\2"+
		"\u00d5\u00d7\t\6\2\2\u00d6\u00d5\3\2\2\2\u00d7\u00d8\3\2\2\2\u00d8\u00d6"+
		"\3\2\2\2\u00d8\u00d9\3\2\2\2\u00d9H\3\2\2\2\t\2NP^j\u00d2\u00d8\4\2\3"+
		"\2\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}