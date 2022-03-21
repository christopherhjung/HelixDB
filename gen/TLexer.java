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
		Comma=18, Dot=19, Colon=20, Equals=21, Identifier=22, Number=23;
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
			"Dot", "Colon", "Equals", "Identifier", "Number"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, null, null, null, null, "'select'", "'from'", "'insert'", "'create'", 
			"'class'", "'property'", "'where'", "'['", "']'", "'('", "')'", "'{'", 
			"'}'", "','", "'.'", "':'", "'='"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "DelimitedComment", "LineComment", "WS", "NL", "Select", "From", 
			"Insert", "Create", "Class", "Property", "Where", "OpenBracket", "CloseBracket", 
			"OpenParenthesis", "CloseParenthesis", "OpenBrace", "CloseBrace", "Comma", 
			"Dot", "Colon", "Equals", "Identifier", "Number"
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
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\31\u00a5\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\3\2"+
		"\3\2\3\2\3\2\3\2\7\2\67\n\2\f\2\16\2:\13\2\3\2\3\2\3\2\3\2\3\2\3\3\3\3"+
		"\3\3\3\3\7\3E\n\3\f\3\16\3H\13\3\3\3\3\3\3\4\3\4\3\4\3\4\3\5\3\5\3\5\5"+
		"\5S\n\5\3\5\3\5\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\7\3\7\3\7\3\7\3\7\3\b\3"+
		"\b\3\b\3\b\3\b\3\b\3\b\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\n\3\n\3\n\3\n\3\n"+
		"\3\n\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\f\3\f\3\f\3\f\3\f"+
		"\3\f\3\r\3\r\3\16\3\16\3\17\3\17\3\20\3\20\3\21\3\21\3\22\3\22\3\23\3"+
		"\23\3\24\3\24\3\25\3\25\3\26\3\26\3\27\3\27\7\27\u009c\n\27\f\27\16\27"+
		"\u009f\13\27\3\30\6\30\u00a2\n\30\r\30\16\30\u00a3\38\2\31\3\3\5\4\7\5"+
		"\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35\20\37\21!\22#\23"+
		"%\24\'\25)\26+\27-\30/\31\3\2\7\4\2\f\f\17\17\5\2\13\13\16\16\"\"\4\2"+
		"C\\c|\5\2C\\aac|\3\2\62;\2\u00aa\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2"+
		"\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2"+
		"\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2"+
		"\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2"+
		"\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2\3\61\3\2\2\2\5@\3\2\2\2\7K\3\2\2\2\t"+
		"R\3\2\2\2\13V\3\2\2\2\r]\3\2\2\2\17b\3\2\2\2\21i\3\2\2\2\23p\3\2\2\2\25"+
		"v\3\2\2\2\27\177\3\2\2\2\31\u0085\3\2\2\2\33\u0087\3\2\2\2\35\u0089\3"+
		"\2\2\2\37\u008b\3\2\2\2!\u008d\3\2\2\2#\u008f\3\2\2\2%\u0091\3\2\2\2\'"+
		"\u0093\3\2\2\2)\u0095\3\2\2\2+\u0097\3\2\2\2-\u0099\3\2\2\2/\u00a1\3\2"+
		"\2\2\61\62\7\61\2\2\62\63\7,\2\2\638\3\2\2\2\64\67\5\3\2\2\65\67\13\2"+
		"\2\2\66\64\3\2\2\2\66\65\3\2\2\2\67:\3\2\2\289\3\2\2\28\66\3\2\2\29;\3"+
		"\2\2\2:8\3\2\2\2;<\7,\2\2<=\7\61\2\2=>\3\2\2\2>?\b\2\2\2?\4\3\2\2\2@A"+
		"\7\61\2\2AB\7\61\2\2BF\3\2\2\2CE\n\2\2\2DC\3\2\2\2EH\3\2\2\2FD\3\2\2\2"+
		"FG\3\2\2\2GI\3\2\2\2HF\3\2\2\2IJ\b\3\2\2J\6\3\2\2\2KL\t\3\2\2LM\3\2\2"+
		"\2MN\b\4\3\2N\b\3\2\2\2OS\7\f\2\2PQ\7\17\2\2QS\7\f\2\2RO\3\2\2\2RP\3\2"+
		"\2\2ST\3\2\2\2TU\b\5\3\2U\n\3\2\2\2VW\7u\2\2WX\7g\2\2XY\7n\2\2YZ\7g\2"+
		"\2Z[\7e\2\2[\\\7v\2\2\\\f\3\2\2\2]^\7h\2\2^_\7t\2\2_`\7q\2\2`a\7o\2\2"+
		"a\16\3\2\2\2bc\7k\2\2cd\7p\2\2de\7u\2\2ef\7g\2\2fg\7t\2\2gh\7v\2\2h\20"+
		"\3\2\2\2ij\7e\2\2jk\7t\2\2kl\7g\2\2lm\7c\2\2mn\7v\2\2no\7g\2\2o\22\3\2"+
		"\2\2pq\7e\2\2qr\7n\2\2rs\7c\2\2st\7u\2\2tu\7u\2\2u\24\3\2\2\2vw\7r\2\2"+
		"wx\7t\2\2xy\7q\2\2yz\7r\2\2z{\7g\2\2{|\7t\2\2|}\7v\2\2}~\7{\2\2~\26\3"+
		"\2\2\2\177\u0080\7y\2\2\u0080\u0081\7j\2\2\u0081\u0082\7g\2\2\u0082\u0083"+
		"\7t\2\2\u0083\u0084\7g\2\2\u0084\30\3\2\2\2\u0085\u0086\7]\2\2\u0086\32"+
		"\3\2\2\2\u0087\u0088\7_\2\2\u0088\34\3\2\2\2\u0089\u008a\7*\2\2\u008a"+
		"\36\3\2\2\2\u008b\u008c\7+\2\2\u008c \3\2\2\2\u008d\u008e\7}\2\2\u008e"+
		"\"\3\2\2\2\u008f\u0090\7\177\2\2\u0090$\3\2\2\2\u0091\u0092\7.\2\2\u0092"+
		"&\3\2\2\2\u0093\u0094\7\60\2\2\u0094(\3\2\2\2\u0095\u0096\7<\2\2\u0096"+
		"*\3\2\2\2\u0097\u0098\7?\2\2\u0098,\3\2\2\2\u0099\u009d\t\4\2\2\u009a"+
		"\u009c\t\5\2\2\u009b\u009a\3\2\2\2\u009c\u009f\3\2\2\2\u009d\u009b\3\2"+
		"\2\2\u009d\u009e\3\2\2\2\u009e.\3\2\2\2\u009f\u009d\3\2\2\2\u00a0\u00a2"+
		"\t\6\2\2\u00a1\u00a0\3\2\2\2\u00a2\u00a3\3\2\2\2\u00a3\u00a1\3\2\2\2\u00a3"+
		"\u00a4\3\2\2\2\u00a4\60\3\2\2\2\t\2\668FR\u009d\u00a3\4\2\3\2\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}