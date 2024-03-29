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
		Create=8, Class=9, Property=10, OpenBracket=11, CloseBracket=12, OpenParenthesis=13, 
		CloseParenthesis=14, OpenBrace=15, CloseBrace=16, Comma=17, Dot=18, Colon=19, 
		Equals=20, Identifier=21, Number=22;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"DelimitedComment", "LineComment", "WS", "NL", "Select", "From", "Insert", 
			"Create", "Class", "Property", "OpenBracket", "CloseBracket", "OpenParenthesis", 
			"CloseParenthesis", "OpenBrace", "CloseBrace", "Comma", "Dot", "Colon", 
			"Equals", "Identifier", "Number"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, null, null, null, null, "'select'", "'from'", "'insert'", "'create'", 
			"'class'", "'property'", "'['", "']'", "'('", "')'", "'{'", "'}'", "','", 
			"'.'", "':'", "'='"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "DelimitedComment", "LineComment", "WS", "NL", "Select", "From", 
			"Insert", "Create", "Class", "Property", "OpenBracket", "CloseBracket", 
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
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\30\u009d\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\3\2\3\2\3\2\3"+
		"\2\3\2\7\2\65\n\2\f\2\16\28\13\2\3\2\3\2\3\2\3\2\3\2\3\3\3\3\3\3\3\3\7"+
		"\3C\n\3\f\3\16\3F\13\3\3\3\3\3\3\4\3\4\3\4\3\4\3\5\3\5\3\5\5\5Q\n\5\3"+
		"\5\3\5\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\7\3\7\3\7\3\7\3\7\3\b\3\b\3\b\3\b"+
		"\3\b\3\b\3\b\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\n\3\n\3\n\3\n\3\n\3\n\3\13"+
		"\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\f\3\f\3\r\3\r\3\16\3\16\3\17"+
		"\3\17\3\20\3\20\3\21\3\21\3\22\3\22\3\23\3\23\3\24\3\24\3\25\3\25\3\26"+
		"\3\26\7\26\u0094\n\26\f\26\16\26\u0097\13\26\3\27\6\27\u009a\n\27\r\27"+
		"\16\27\u009b\3\66\2\30\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27"+
		"\r\31\16\33\17\35\20\37\21!\22#\23%\24\'\25)\26+\27-\30\3\2\7\4\2\f\f"+
		"\17\17\5\2\13\13\16\16\"\"\4\2C\\c|\5\2C\\aac|\3\2\62;\2\u00a2\2\3\3\2"+
		"\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17"+
		"\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2"+
		"\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3"+
		"\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\3/\3\2\2\2\5>\3\2"+
		"\2\2\7I\3\2\2\2\tP\3\2\2\2\13T\3\2\2\2\r[\3\2\2\2\17`\3\2\2\2\21g\3\2"+
		"\2\2\23n\3\2\2\2\25t\3\2\2\2\27}\3\2\2\2\31\177\3\2\2\2\33\u0081\3\2\2"+
		"\2\35\u0083\3\2\2\2\37\u0085\3\2\2\2!\u0087\3\2\2\2#\u0089\3\2\2\2%\u008b"+
		"\3\2\2\2\'\u008d\3\2\2\2)\u008f\3\2\2\2+\u0091\3\2\2\2-\u0099\3\2\2\2"+
		"/\60\7\61\2\2\60\61\7,\2\2\61\66\3\2\2\2\62\65\5\3\2\2\63\65\13\2\2\2"+
		"\64\62\3\2\2\2\64\63\3\2\2\2\658\3\2\2\2\66\67\3\2\2\2\66\64\3\2\2\2\67"+
		"9\3\2\2\28\66\3\2\2\29:\7,\2\2:;\7\61\2\2;<\3\2\2\2<=\b\2\2\2=\4\3\2\2"+
		"\2>?\7\61\2\2?@\7\61\2\2@D\3\2\2\2AC\n\2\2\2BA\3\2\2\2CF\3\2\2\2DB\3\2"+
		"\2\2DE\3\2\2\2EG\3\2\2\2FD\3\2\2\2GH\b\3\2\2H\6\3\2\2\2IJ\t\3\2\2JK\3"+
		"\2\2\2KL\b\4\3\2L\b\3\2\2\2MQ\7\f\2\2NO\7\17\2\2OQ\7\f\2\2PM\3\2\2\2P"+
		"N\3\2\2\2QR\3\2\2\2RS\b\5\3\2S\n\3\2\2\2TU\7u\2\2UV\7g\2\2VW\7n\2\2WX"+
		"\7g\2\2XY\7e\2\2YZ\7v\2\2Z\f\3\2\2\2[\\\7h\2\2\\]\7t\2\2]^\7q\2\2^_\7"+
		"o\2\2_\16\3\2\2\2`a\7k\2\2ab\7p\2\2bc\7u\2\2cd\7g\2\2de\7t\2\2ef\7v\2"+
		"\2f\20\3\2\2\2gh\7e\2\2hi\7t\2\2ij\7g\2\2jk\7c\2\2kl\7v\2\2lm\7g\2\2m"+
		"\22\3\2\2\2no\7e\2\2op\7n\2\2pq\7c\2\2qr\7u\2\2rs\7u\2\2s\24\3\2\2\2t"+
		"u\7r\2\2uv\7t\2\2vw\7q\2\2wx\7r\2\2xy\7g\2\2yz\7t\2\2z{\7v\2\2{|\7{\2"+
		"\2|\26\3\2\2\2}~\7]\2\2~\30\3\2\2\2\177\u0080\7_\2\2\u0080\32\3\2\2\2"+
		"\u0081\u0082\7*\2\2\u0082\34\3\2\2\2\u0083\u0084\7+\2\2\u0084\36\3\2\2"+
		"\2\u0085\u0086\7}\2\2\u0086 \3\2\2\2\u0087\u0088\7\177\2\2\u0088\"\3\2"+
		"\2\2\u0089\u008a\7.\2\2\u008a$\3\2\2\2\u008b\u008c\7\60\2\2\u008c&\3\2"+
		"\2\2\u008d\u008e\7<\2\2\u008e(\3\2\2\2\u008f\u0090\7?\2\2\u0090*\3\2\2"+
		"\2\u0091\u0095\t\4\2\2\u0092\u0094\t\5\2\2\u0093\u0092\3\2\2\2\u0094\u0097"+
		"\3\2\2\2\u0095\u0093\3\2\2\2\u0095\u0096\3\2\2\2\u0096,\3\2\2\2\u0097"+
		"\u0095\3\2\2\2\u0098\u009a\t\6\2\2\u0099\u0098\3\2\2\2\u009a\u009b\3\2"+
		"\2\2\u009b\u0099\3\2\2\2\u009b\u009c\3\2\2\2\u009c.\3\2\2\2\t\2\64\66"+
		"DP\u0095\u009b\4\2\3\2\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}