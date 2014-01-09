/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse         pltsql_yyparse
#define yylex           pltsql_yylex
#define yyerror         pltsql_yyerror
#define yylval          pltsql_yylval
#define yychar          pltsql_yychar
#define yydebug         pltsql_yydebug
#define yynerrs         pltsql_yynerrs
#define yylloc          pltsql_yylloc

/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "src/gram.y"

/*--------------------------------------------------------------------------------------------
 *
 * gram.y				- Parser for the PL/TSQL procedural language
 *
 * Portions Copyright (c) 2011-2014, Open Source Consulting Group, Inc.  All rights reserved.
 *
 * Portions Copyright (c) 1996-2011, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *	  src/gram.y
 *
 *--------------------------------------------------------------------------------------------
 */

#include "pltsql.h"

#include "catalog/namespace.h"
#include "catalog/pg_type.h"
#include "parser/parser.h"
#include "parser/parse_type.h"
#include "parser/scanner.h"
#include "parser/scansup.h"
#include "utils/builtins.h"


/* Location tracking support --- simpler than bison's default */
#define YYLLOC_DEFAULT(Current, Rhs, N) \
	do { \
		if (N) \
			(Current) = (Rhs)[1]; \
		else \
			(Current) = (Rhs)[0]; \
	} while (0)

/*
 * Bison doesn't allocate anything that needs to live across parser calls,
 * so we can easily have it use palloc instead of malloc.  This prevents
 * memory leaks if we error out during parsing.  Note this only works with
 * bison >= 2.0.  However, in bison 1.875 the default is to use alloca()
 * if possible, so there's not really much problem anyhow, at least if
 * you're building with gcc.
 */
#define YYMALLOC palloc
#define YYFREE   pfree

#define TEMPOBJ_QUALIFIER "TEMPORARY "

typedef struct
{
	int			location;
	int			leaderlen;
} sql_error_callback_arg;

typedef struct
{
	int			location;
	char		*ident;
} tsql_ident_ref;

#define parser_errposition(pos)  pltsql_scanner_errposition(pos)

union YYSTYPE;					/* need forward reference for tok_is_keyword */

static	bool			tok_is_keyword(int token, union YYSTYPE *lval,
									   int kw_token, const char *kw_str);
static	void			word_is_not_variable(PLword *word, int location);
static	void			cword_is_not_variable(PLcword *cword, int location);
static	void			current_token_is_not_variable(int tok);
static	char *			quote_tsql_identifiers(const StringInfo src,
											const List *tsql_word_list);
static List * append_if_tsql_identifier(int tok, int start_len, int start_loc,
											List *tsql_idents);
static	PLTSQL_expr	*read_sql_construct(int until,
											int until2,
											int until3,
											const char *expected,
											const char *sqlstart,
											bool isexpression,
											bool valid_sql,
											bool trim,
											int *startloc,
											int *endtoken);
static	PLTSQL_expr	*read_sql_construct_bos(int until,
											int until2,
											int until3,
											const char *expected,
											const char *sqlstart,
											bool isexpression,
											bool valid_sql,
											bool trim,
											int *startloc,
											int *endtoken,
											bool untilbostok);
static	PLTSQL_expr	*read_sql_expression(int until,
											 const char *expected);
static	PLTSQL_expr	*read_sql_expression_bos(int until,
											 const char *expected);
static	PLTSQL_expr	*read_sql_expression2(int until, int until2,
											  const char *expected,
											  int *endtoken);
static PLTSQL_expr * read_sql_expression2_bos(int until, int until2,
											  const char *expected,
											  int *endtoken);
static bool is_terminator(int tok, bool first, int start_loc, int cur_loc,
                          const char *sql_start, const List *tsql_idents);
static bool word_matches(int tok, const char *pattern);
static	PLTSQL_expr	*read_sql_stmt(const char *sqlstart);
static	PLTSQL_expr	*read_sql_stmt_bos(const char *sqlstart);
static	PLTSQL_type	*read_datatype(int tok);
static	PLTSQL_stmt	*make_execsql_stmt(int firsttoken, int location,
										 PLword *firstword);
static	PLTSQL_stmt_fetch *read_fetch_direction(void);
static	void			 complete_direction(PLTSQL_stmt_fetch *fetch,
											bool *check_FROM);
static	PLTSQL_stmt	*make_return_stmt(int location);
static	PLTSQL_stmt	*make_return_next_stmt(int location);
static	PLTSQL_stmt	*make_return_query_stmt(int location);
static	char			*NameOfDatum(PLwdatum *wdatum);
static	void			 check_assignable(PLTSQL_datum *datum, int location);
static	void			 read_into_target(PLTSQL_rec **rec, PLTSQL_row **row,
										  bool *strict);
static	PLTSQL_row		*read_into_scalar_list(char *initial_name,
											   PLTSQL_datum *initial_datum,
											   int initial_location);
static	PLTSQL_row		*make_scalar_list1(char *initial_name,
										   PLTSQL_datum *initial_datum,
										   int lineno, int location);
static	void			 check_sql_expr(const char *stmt, int location,
										int leaderlen);
static	void			 pltsql_sql_error_callback(void *arg);
static	PLTSQL_type	*parse_datatype(const char *string, int location);
static	void			 check_labels(const char *start_label,
									  const char *end_label,
									  int end_location);
static	PLTSQL_expr	*read_cursor_args(PLTSQL_var *cursor,
										  int until, const char *expected);
static	List			*read_raise_options(void);



/* Line 268 of yacc.c  */
#line 223 "src/pl_gram.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENT = 258,
     FCONST = 259,
     SCONST = 260,
     BCONST = 261,
     XCONST = 262,
     Op = 263,
     ICONST = 264,
     PARAM = 265,
     TYPECAST = 266,
     DOT_DOT = 267,
     COLON_EQUALS = 268,
     T_WORD = 269,
     T_CWORD = 270,
     T_DATUM = 271,
     LESS_LESS = 272,
     GREATER_GREATER = 273,
     K_ABSOLUTE = 274,
     K_ALIAS = 275,
     K_ALL = 276,
     K_ARRAY = 277,
     K_BACKWARD = 278,
     K_BEGIN = 279,
     K_BY = 280,
     K_CASE = 281,
     K_CLOSE = 282,
     K_COLLATE = 283,
     K_CONSTANT = 284,
     K_CONTINUE = 285,
     K_CURRENT = 286,
     K_CURSOR = 287,
     K_DEBUG = 288,
     K_DECLARE = 289,
     K_DEFAULT = 290,
     K_DETAIL = 291,
     K_DIAGNOSTICS = 292,
     K_DUMP = 293,
     K_ELSE = 294,
     K_ELSIF = 295,
     K_END = 296,
     K_ERRCODE = 297,
     K_ERROR = 298,
     K_EXCEPTION = 299,
     K_EXECUTE = 300,
     K_EXIT = 301,
     K_FETCH = 302,
     K_FIRST = 303,
     K_FOR = 304,
     K_FOREACH = 305,
     K_FORWARD = 306,
     K_FROM = 307,
     K_GET = 308,
     K_HINT = 309,
     K_IF = 310,
     K_IN = 311,
     K_INFO = 312,
     K_INSERT = 313,
     K_INTO = 314,
     K_IS = 315,
     K_LAST = 316,
     K_LOG = 317,
     K_LOOP = 318,
     K_MESSAGE = 319,
     K_MESSAGE_TEXT = 320,
     K_MOVE = 321,
     K_NEXT = 322,
     K_NO = 323,
     K_NOT = 324,
     K_NOTICE = 325,
     K_NULL = 326,
     K_OPEN = 327,
     K_OPTION = 328,
     K_OR = 329,
     K_PERFORM = 330,
     K_PG_EXCEPTION_CONTEXT = 331,
     K_PG_EXCEPTION_DETAIL = 332,
     K_PG_EXCEPTION_HINT = 333,
     K_PRIOR = 334,
     K_QUERY = 335,
     K_RAISE = 336,
     K_RELATIVE = 337,
     K_RESULT_OID = 338,
     K_RETURN = 339,
     K_RETURNED_SQLSTATE = 340,
     K_REVERSE = 341,
     K_ROWTYPE = 342,
     K_ROW_COUNT = 343,
     K_SCROLL = 344,
     K_SLICE = 345,
     K_SQLSTATE = 346,
     K_STACKED = 347,
     K_STRICT = 348,
     K_THEN = 349,
     K_TO = 350,
     K_TYPE = 351,
     K_USE_COLUMN = 352,
     K_USE_VARIABLE = 353,
     K_USING = 354,
     K_VARIABLE_CONFLICT = 355,
     K_WARNING = 356,
     K_WHEN = 357,
     K_WHILE = 358,
     K_PRINT = 359,
     K_SET = 360,
     LOWER_THAN_ELSE = 361
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 148 "src/gram.y"

		core_YYSTYPE			core_yystype;
		/* these fields must match core_YYSTYPE: */
		int						ival;
		char					*str;
		const char				*keyword;

		PLword					word;
		PLcword					cword;
		PLwdatum				wdatum;
		bool					boolean;
		Oid						oid;
		struct
		{
			char *name;
			int  lineno;
		}						varname;
		struct
		{
			char *name;
			int  lineno;
			PLTSQL_datum   *scalar;
			PLTSQL_rec		*rec;
			PLTSQL_row		*row;
		}						forvariable;
		struct
		{
			char *label;
			int  n_initvars;
			int  *initvarnos;
		}						declhdr;
		struct
		{
			List *stmts;
			char *end_label;
			int   end_label_location;
		}						loop_body;
		List					*list;
		PLTSQL_type			*dtype;
		PLTSQL_datum			*datum;
		PLTSQL_var				*var;
		PLTSQL_expr			*expr;
		PLTSQL_stmt			*stmt;
		PLTSQL_condition		*condition;
		PLTSQL_exception		*exception;
		PLTSQL_exception_block	*exception_block;
		PLTSQL_nsitem			*nsitem;
		PLTSQL_diag_item		*diagitem;
		PLTSQL_stmt_fetch		*fetch;



/* Line 293 of yacc.c  */
#line 418 "src/pl_gram.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 443 "src/pl_gram.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   593

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  114
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  83
/* YYNRULES -- Number of rules.  */
#define YYNRULES  205
/* YYNRULES -- Number of states.  */
#define YYNSTATES  268

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   361

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,   107,     2,     2,     2,     2,
     110,   111,     2,     2,   109,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   108,
       2,   112,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   113,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,     8,    11,    15,    19,    23,    27,
      28,    30,    31,    33,    35,    41,    43,    46,    50,    52,
      55,    57,    59,    61,    65,    72,    78,    79,    87,    88,
      91,    93,    94,    95,    99,   101,   105,   108,   110,   112,
     114,   116,   118,   120,   121,   123,   124,   125,   128,   131,
     132,   135,   137,   139,   141,   143,   145,   147,   149,   151,
     153,   155,   156,   158,   161,   163,   165,   167,   169,   171,
     173,   175,   177,   179,   181,   183,   185,   187,   189,   191,
     193,   195,   197,   199,   201,   203,   205,   207,   209,   212,
     213,   215,   220,   226,   227,   229,   231,   235,   237,   241,
     242,   244,   246,   248,   250,   254,   258,   264,   268,   274,
     279,   284,   287,   289,   291,   293,   302,   303,   306,   310,
     312,   314,   316,   318,   320,   326,   328,   330,   332,   334,
     337,   342,   347,   348,   352,   355,   357,   359,   361,   362,
     363,   367,   370,   372,   377,   381,   383,   385,   386,   387,
     388,   389,   390,   391,   395,   396,   398,   400,   403,   405,
     407,   409,   411,   413,   415,   417,   419,   421,   423,   425,
     427,   429,   431,   433,   435,   437,   439,   441,   443,   445,
     447,   449,   451,   453,   455,   457,   459,   461,   463,   465,
     467,   469,   471,   473,   475,   477,   479,   481,   483,   485,
     487,   489,   491,   493,   495,   497
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     115,     0,    -1,   116,   120,   118,    -1,    -1,   116,   117,
      -1,   107,    73,    38,    -1,   107,   100,    43,    -1,   107,
     100,    98,    -1,   107,   100,    97,    -1,    -1,   108,    -1,
      -1,   109,    -1,   108,    -1,   121,    24,   142,   181,    41,
      -1,   192,    -1,   192,   122,    -1,   192,   122,   123,    -1,
      34,    -1,   123,   124,    -1,   124,    -1,   125,    -1,    34,
      -1,    17,   195,    18,    -1,   134,   135,   136,   137,   138,
     139,    -1,   134,    20,    49,   133,   119,    -1,    -1,   134,
     127,    32,   126,   129,   132,   128,    -1,    -1,    68,    89,
      -1,    89,    -1,    -1,    -1,   110,   130,   111,    -1,   131,
      -1,   130,   109,   131,    -1,   134,   136,    -1,    60,    -1,
      49,    -1,    14,    -1,    15,    -1,    14,    -1,   196,    -1,
      -1,    29,    -1,    -1,    -1,    28,    14,    -1,    28,    15,
      -1,    -1,    69,    71,    -1,   108,    -1,   109,    -1,    34,
      -1,    24,    -1,    14,    -1,   140,    -1,   141,    -1,    35,
      -1,   112,    -1,    13,    -1,    -1,   143,    -1,   143,   144,
      -1,   144,    -1,   145,    -1,   146,    -1,   147,    -1,   120,
      -1,   150,    -1,   158,    -1,   160,    -1,   161,    -1,   164,
      -1,   166,    -1,   168,    -1,   169,    -1,   172,    -1,   173,
      -1,   148,    -1,   151,    -1,   174,    -1,   175,    -1,   176,
      -1,   178,    -1,   179,    -1,   159,    -1,   170,    -1,    75,
     188,    -1,    -1,   105,    -1,   149,   157,   141,   188,    -1,
      53,   152,    37,   153,   118,    -1,    -1,    31,    -1,    92,
      -1,   153,   109,   154,    -1,   154,    -1,   156,   141,   155,
      -1,    -1,    16,    -1,    14,    -1,    15,    -1,    16,    -1,
     157,   113,   190,    -1,    55,   189,   144,    -1,    55,   189,
     144,    39,   144,    -1,   192,    63,   171,    -1,   192,   103,
     189,    63,   171,    -1,   192,   103,   189,   145,    -1,   192,
      49,   162,   171,    -1,   163,    56,    -1,    16,    -1,    14,
      -1,    15,    -1,   192,    50,   163,   165,    56,    22,   191,
     171,    -1,    -1,    90,     9,    -1,   167,   193,   194,    -1,
      46,    -1,    30,    -1,    84,    -1,    81,    -1,   104,    -1,
     142,    41,    63,   193,   108,    -1,    58,    -1,    14,    -1,
      15,    -1,    45,    -1,    72,   180,    -1,    47,   177,   180,
      59,    -1,    66,   177,   180,   118,    -1,    -1,    27,   180,
     118,    -1,    71,   108,    -1,    16,    -1,    14,    -1,    15,
      -1,    -1,    -1,    44,   182,   183,    -1,   183,   184,    -1,
     184,    -1,   102,   185,    94,   142,    -1,   185,    74,   186,
      -1,   186,    -1,   195,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    17,   195,    18,    -1,    -1,   195,    -1,   108,    -1,
     102,   187,    -1,    14,    -1,    16,    -1,    19,    -1,    20,
      -1,    22,    -1,    23,    -1,    29,    -1,    31,    -1,    32,
      -1,    33,    -1,    36,    -1,    38,    -1,    42,    -1,    43,
      -1,    48,    -1,    51,    -1,    54,    -1,    57,    -1,    60,
      -1,    61,    -1,    62,    -1,    64,    -1,    65,    -1,    67,
      -1,    68,    -1,    70,    -1,    73,    -1,    76,    -1,    77,
      -1,    78,    -1,    79,    -1,    80,    -1,    82,    -1,    83,
      -1,    85,    -1,    86,    -1,    88,    -1,    87,    -1,    89,
      -1,   105,    -1,    90,    -1,    91,    -1,    92,    -1,    96,
      -1,    97,    -1,    98,    -1,   100,    -1,   101,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   365,   365,   371,   372,   375,   379,   383,   387,   393,
     394,   397,   398,   399,   402,   439,   447,   454,   463,   475,
     476,   479,   480,   484,   497,   552,   558,   557,   610,   613,
     617,   624,   630,   633,   662,   666,   672,   680,   681,   683,
     698,   726,   739,   755,   756,   761,   772,   773,   778,   785,
     786,   790,   792,   794,   799,   804,   809,   815,   816,   819,
     820,   824,   825,   829,   836,   845,   846,   847,   850,   852,
     854,   856,   858,   860,   862,   864,   866,   868,   870,   872,
     874,   876,   878,   880,   882,   884,   887,   891,   895,   908,
     909,   913,   927,   982,   985,   989,   995,   999,  1005,  1018,
    1047,  1059,  1064,  1072,  1077,  1094,  1106,  1121,  1138,  1154,
    1173,  1207,  1469,  1501,  1516,  1523,  1566,  1569,  1575,  1590,
    1594,  1600,  1626,  1765,  1823,  1841,  1845,  1855,  1867,  1931,
    2008,  2040,  2053,  2058,  2071,  2078,  2094,  2099,  2107,  2109,
    2108,  2148,  2152,  2158,  2171,  2180,  2186,  2223,  2227,  2231,
    2235,  2239,  2243,  2247,  2255,  2258,  2266,  2268,  2275,  2279,
    2288,  2289,  2290,  2291,  2292,  2293,  2294,  2295,  2296,  2297,
    2298,  2299,  2300,  2301,  2302,  2303,  2304,  2305,  2306,  2307,
    2308,  2309,  2310,  2311,  2312,  2313,  2314,  2315,  2316,  2317,
    2318,  2319,  2320,  2321,  2322,  2323,  2324,  2325,  2326,  2327,
    2328,  2329,  2330,  2331,  2332,  2333
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENT", "FCONST", "SCONST", "BCONST",
  "XCONST", "Op", "ICONST", "PARAM", "TYPECAST", "DOT_DOT", "COLON_EQUALS",
  "T_WORD", "T_CWORD", "T_DATUM", "LESS_LESS", "GREATER_GREATER",
  "K_ABSOLUTE", "K_ALIAS", "K_ALL", "K_ARRAY", "K_BACKWARD", "K_BEGIN",
  "K_BY", "K_CASE", "K_CLOSE", "K_COLLATE", "K_CONSTANT", "K_CONTINUE",
  "K_CURRENT", "K_CURSOR", "K_DEBUG", "K_DECLARE", "K_DEFAULT", "K_DETAIL",
  "K_DIAGNOSTICS", "K_DUMP", "K_ELSE", "K_ELSIF", "K_END", "K_ERRCODE",
  "K_ERROR", "K_EXCEPTION", "K_EXECUTE", "K_EXIT", "K_FETCH", "K_FIRST",
  "K_FOR", "K_FOREACH", "K_FORWARD", "K_FROM", "K_GET", "K_HINT", "K_IF",
  "K_IN", "K_INFO", "K_INSERT", "K_INTO", "K_IS", "K_LAST", "K_LOG",
  "K_LOOP", "K_MESSAGE", "K_MESSAGE_TEXT", "K_MOVE", "K_NEXT", "K_NO",
  "K_NOT", "K_NOTICE", "K_NULL", "K_OPEN", "K_OPTION", "K_OR", "K_PERFORM",
  "K_PG_EXCEPTION_CONTEXT", "K_PG_EXCEPTION_DETAIL", "K_PG_EXCEPTION_HINT",
  "K_PRIOR", "K_QUERY", "K_RAISE", "K_RELATIVE", "K_RESULT_OID",
  "K_RETURN", "K_RETURNED_SQLSTATE", "K_REVERSE", "K_ROWTYPE",
  "K_ROW_COUNT", "K_SCROLL", "K_SLICE", "K_SQLSTATE", "K_STACKED",
  "K_STRICT", "K_THEN", "K_TO", "K_TYPE", "K_USE_COLUMN", "K_USE_VARIABLE",
  "K_USING", "K_VARIABLE_CONFLICT", "K_WARNING", "K_WHEN", "K_WHILE",
  "K_PRINT", "K_SET", "LOWER_THAN_ELSE", "'#'", "';'", "','", "'('", "')'",
  "'='", "'['", "$accept", "pl_function", "comp_options", "comp_option",
  "opt_semi", "opt_semi_or_commma", "pl_block", "decl_sect", "decl_start",
  "decl_stmts", "decl_stmt", "decl_statement", "$@1", "opt_scrollable",
  "decl_cursor_query", "decl_cursor_args", "decl_cursor_arglist",
  "decl_cursor_arg", "decl_is_for", "decl_aliasitem", "decl_varname",
  "decl_const", "decl_datatype", "decl_collate", "decl_notnull",
  "decl_defval", "decl_defkey", "assign_operator", "proc_sect",
  "proc_stmts", "proc_stmt", "common_stmt", "plpgsql_only_stmt",
  "pltsql_only_stmt", "stmt_perform", "opt_set", "stmt_assign",
  "stmt_getdiag", "getdiag_area_opt", "getdiag_list", "getdiag_list_item",
  "getdiag_item", "getdiag_target", "assign_var", "stmt_if", "stmt_loop",
  "stmt_while", "stmt_for", "for_control", "for_variable",
  "stmt_foreach_a", "foreach_slice", "stmt_exit", "exit_type",
  "stmt_return", "stmt_raise", "stmt_print", "loop_body", "stmt_execsql",
  "stmt_dynexecute", "stmt_open", "stmt_fetch", "stmt_move",
  "opt_fetch_direction", "stmt_close", "stmt_null", "cursor_variable",
  "exception_sect", "@2", "proc_exceptions", "proc_exception",
  "proc_conditions", "proc_condition", "expr_until_semi",
  "expr_until_semi_or_bos", "expr_until_bos", "expr_until_rightbracket",
  "expr_until_loop", "opt_block_label", "opt_label", "opt_exitcond",
  "any_identifier", "unreserved_keyword", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,    35,    59,    44,
      40,    41,    61,    91
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   114,   115,   116,   116,   117,   117,   117,   117,   118,
     118,   119,   119,   119,   120,   121,   121,   121,   122,   123,
     123,   124,   124,   124,   125,   125,   126,   125,   127,   127,
     127,   128,   129,   129,   130,   130,   131,   132,   132,   133,
     133,   134,   134,   135,   135,   136,   137,   137,   137,   138,
     138,   139,   139,   139,   139,   139,   139,   140,   140,   141,
     141,   142,   142,   143,   143,   144,   144,   144,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   146,   147,   148,   149,
     149,   150,   151,   152,   152,   152,   153,   153,   154,   155,
     156,   156,   156,   157,   157,   158,   158,   159,   160,   160,
     161,   162,   163,   163,   163,   164,   165,   165,   166,   167,
     167,   168,   169,   170,   171,   172,   172,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   180,   180,   181,   182,
     181,   183,   183,   184,   185,   185,   186,   187,   188,   189,
     190,   191,   192,   192,   193,   193,   194,   194,   195,   195,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   196
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     0,     2,     3,     3,     3,     3,     0,
       1,     0,     1,     1,     5,     1,     2,     3,     1,     2,
       1,     1,     1,     3,     6,     5,     0,     7,     0,     2,
       1,     0,     0,     3,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     0,     1,     0,     0,     2,     2,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     0,
       1,     4,     5,     0,     1,     1,     3,     1,     3,     0,
       1,     1,     1,     1,     3,     3,     5,     3,     5,     4,
       4,     2,     1,     1,     1,     8,     0,     2,     3,     1,
       1,     1,     1,     1,     5,     1,     1,     1,     1,     2,
       4,     4,     0,     3,     2,     1,     1,     1,     0,     0,
       3,     2,     1,     4,     3,     1,     1,     0,     0,     0,
       0,     0,     0,     3,     0,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,   152,     1,     0,     0,     4,     9,     0,    15,
     158,   159,     0,     0,     0,    10,     2,   152,    18,    16,
     153,     5,     6,     8,     7,   126,   127,     0,   120,   128,
     119,   132,    93,   149,   125,   132,     0,     0,   148,   122,
     121,   123,    90,    68,   138,   152,    64,    65,    66,    67,
      79,     0,    69,    80,    70,    86,    71,    72,    73,    74,
     154,    75,    76,    87,    77,    78,    81,    82,    83,    84,
      85,    15,    41,     0,   160,   161,   162,   163,   164,   165,
     166,   167,    22,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   195,
     194,   196,   198,   199,   200,   201,   202,   203,   204,   205,
     197,    17,    20,    21,    43,    42,   136,   137,   135,     9,
       0,    94,    95,     0,   152,     0,   134,   129,    88,   139,
       0,    63,   103,     0,     0,   155,     0,     0,   152,   149,
       0,    19,     0,    44,     0,    30,     0,    45,   133,     0,
       0,   105,     9,     0,    14,    60,    59,   150,   148,   147,
     156,   118,   113,   114,   112,   152,     0,   116,     0,   107,
     152,    23,     0,    29,    26,    46,   130,   101,   102,   100,
       9,    97,     0,   152,   131,     0,   140,   142,   104,    91,
     157,   110,   111,     0,     0,     0,   152,   109,    15,    39,
      40,    11,    32,     0,    49,     0,    92,    99,   106,     0,
     145,   146,   141,   117,     0,   154,   108,    13,    12,    25,
       0,     0,    47,    48,     0,     0,    96,    98,     0,   152,
     151,     0,     0,    34,    45,    38,    37,    31,    50,    55,
      54,    53,    58,    51,    52,    24,    56,    57,   144,   143,
     152,   124,     0,    33,    36,    27,   115,    35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,    16,   229,    43,     8,    19,   121,
     122,   123,   212,   156,   265,   231,   242,   243,   247,   211,
     124,   157,   185,   214,   235,   255,   256,   168,   178,    45,
      46,    47,    48,    49,    50,    51,    52,    53,   133,   190,
     191,   237,   192,   143,    54,    55,    56,    57,   175,   176,
      58,   204,    59,    60,    61,    62,    63,   179,    64,    65,
      66,    67,    68,   130,    69,    70,   129,   140,   163,   196,
     197,   219,   220,   200,   138,   134,   198,   260,    71,   144,
     171,   145,   125
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -216
static const yytype_int16 yypact[] =
{
    -216,    22,   -12,  -216,     9,   -40,  -216,   -62,    34,    29,
    -216,  -216,    50,    36,   -17,  -216,  -216,     4,  -216,    96,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,    40,  -216,  -216,
    -216,  -216,   -19,  -216,  -216,  -216,   -26,    40,  -216,  -216,
    -216,  -216,  -216,  -216,    49,   276,  -216,  -216,  -216,  -216,
    -216,    68,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
       9,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,   -20,  -216,     9,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,    96,  -216,  -216,    32,  -216,  -216,  -216,  -216,   -62,
      40,  -216,  -216,    59,   435,    40,  -216,  -216,  -216,  -216,
      58,  -216,  -216,    -9,   -70,  -216,    51,    51,   382,  -216,
      94,  -216,    65,  -216,    28,  -216,    88,  -216,  -216,    67,
      75,    85,   -62,    31,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,   382,    79,    41,    95,  -216,
     488,  -216,    27,  -216,  -216,   109,  -216,  -216,  -216,  -216,
     -31,  -216,    -5,   435,  -216,     9,    31,  -216,  -216,  -216,
    -216,  -216,  -216,   132,    86,    80,   382,  -216,    37,  -216,
    -216,   -11,    35,   108,    77,    75,  -216,  -216,  -216,   -58,
    -216,  -216,  -216,  -216,   126,     9,  -216,  -216,  -216,  -216,
     184,   -25,  -216,  -216,    78,    -7,  -216,  -216,     9,   329,
    -216,    44,   -72,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
     382,  -216,   184,  -216,  -216,  -216,  -216,  -216
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -216,  -216,  -216,  -216,  -118,  -216,   152,  -216,  -216,  -216,
      38,  -216,  -216,  -216,  -216,  -216,  -216,  -107,  -216,  -216,
    -215,  -216,   -82,  -216,  -216,  -216,  -216,  -182,   -16,  -216,
     -42,   -15,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
     -48,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,    21,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -166,  -216,  -216,
    -216,  -216,  -216,   135,  -216,  -216,   -24,  -216,  -216,  -216,
      -6,  -216,   -67,  -216,    42,    46,  -216,  -216,     0,   -36,
    -216,    -4,  -216
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -90
static const yytype_int16 yytable[] =
{
      12,    44,     9,   141,   165,     4,   165,   249,   165,   201,
     217,   158,   131,   137,    18,   244,   238,   250,    25,    26,
     -89,     4,     3,    10,   245,    11,    22,   251,   252,   146,
     147,    27,   169,    13,    28,   246,   239,   262,   170,   263,
     226,   209,   210,   148,   194,   -61,    15,   244,   -61,    29,
      30,    31,   152,   257,   126,   127,   128,    32,    17,    33,
      14,   153,    34,    18,   -28,   172,   173,   174,    20,   150,
      35,    18,   216,   132,    21,    36,    37,    15,   215,    38,
      23,    24,   136,   149,   142,    39,   146,   147,    40,   187,
     188,   189,   161,   139,   266,     5,   160,   227,   228,   164,
     154,   253,   254,   166,   167,   166,   159,   166,    41,    42,
      72,   162,   181,    73,   182,    74,    75,   183,    76,    77,
     184,   155,   232,   233,   193,    78,   186,    79,    80,    81,
      82,   203,    83,   195,    84,   202,   205,   213,    85,    86,
     149,   223,   224,   225,    87,   230,   234,    88,   240,   248,
      89,   218,   261,    90,     7,   267,    91,    92,    93,   151,
      94,    95,   264,    96,    97,   207,    98,   236,   177,    99,
     135,   258,   100,   101,   102,   103,   104,     0,   105,   106,
     208,   107,   108,   109,   110,   111,   112,   113,   114,   241,
     222,   221,   115,   116,   117,   180,   118,   119,    72,     0,
       0,   120,     0,    74,    75,     0,    76,    77,     0,     0,
     199,     0,     0,    78,     0,    79,    80,    81,     0,     0,
      83,     0,    84,   259,     0,     0,    85,    86,     0,     0,
       0,     0,    87,     0,   221,    88,     0,     0,    89,     0,
       0,    90,     0,     0,    91,    92,    93,     0,    94,    95,
       0,    96,    97,     0,    98,     0,     0,    99,     0,     0,
     100,   101,   102,   103,   104,     0,   105,   106,     0,   107,
     108,   109,   110,   111,   112,   113,   114,     0,     0,     0,
     115,   116,   117,     0,   118,   119,     0,     0,     0,   120,
      25,    26,   -89,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    27,     0,     0,    28,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -62,     0,     0,
     -62,    29,    30,    31,     0,     0,     0,     0,     0,    32,
       0,    33,     0,     0,    34,     0,     0,     0,     0,     0,
       0,     0,    35,    25,    26,   -89,     4,    36,    37,     0,
       0,    38,     0,     0,     0,     0,    27,    39,     0,    28,
      40,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -61,     0,     0,     0,    29,    30,    31,     0,   -62,     0,
      41,    42,    32,     0,    33,     0,     0,    34,     0,     0,
       0,     0,     0,     0,     0,    35,    25,    26,   -89,     4,
      36,    37,     0,     0,    38,     0,     0,     0,     0,    27,
      39,     0,    28,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -61,     0,     0,     0,    29,    30,    31,
       0,   -61,     0,    41,    42,    32,     0,    33,     0,     0,
      34,     0,     0,     0,     0,     0,     0,     0,    35,    25,
      26,   -89,     4,    36,    37,     0,     0,    38,     0,     0,
       0,     0,    27,    39,     0,    28,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      29,    30,    31,     0,     0,     0,    41,    42,    32,     0,
      33,     0,     0,    34,     0,     0,     0,     0,     0,     0,
       0,    35,    25,    26,   -89,     4,    36,    37,     0,     0,
      38,     0,     0,     0,     0,    27,    39,     0,    28,    40,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    29,    30,    31,     0,     0,     0,    41,
      42,    32,     0,    33,     0,     0,    34,     0,     0,     0,
       0,   206,     0,     0,    35,     0,     0,     0,     0,    36,
      37,     0,     0,    38,     0,     0,     0,     0,     0,    39,
       0,     0,    40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    42
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-216))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       4,    17,     2,    45,    13,    17,    13,    14,    13,   175,
     192,   129,    31,    37,    34,   230,    74,    24,    14,    15,
      16,    17,     0,    14,    49,    16,    43,    34,    35,    49,
      50,    27,   102,    73,    30,    60,    94,   109,   108,   111,
     206,    14,    15,    63,   162,    41,   108,   262,    44,    45,
      46,    47,    20,   235,    14,    15,    16,    53,    24,    55,
     100,    29,    58,    34,    32,    14,    15,    16,    18,    73,
      66,    34,   190,    92,    38,    71,    72,   108,   109,    75,
      97,    98,   108,   103,    16,    81,    49,    50,    84,    14,
      15,    16,   134,    44,   260,   107,    37,   108,   109,    41,
      68,   108,   109,   112,   113,   112,   130,   112,   104,   105,
      14,   135,    18,    17,    49,    19,    20,    89,    22,    23,
      32,    89,    14,    15,    39,    29,    59,    31,    32,    33,
      34,    90,    36,   102,    38,    56,    41,    28,    42,    43,
     103,     9,    56,    63,    48,   110,    69,    51,    22,    71,
      54,   193,   108,    57,     2,   262,    60,    61,    62,   121,
      64,    65,   244,    67,    68,   180,    70,   215,   147,    73,
      35,   238,    76,    77,    78,    79,    80,    -1,    82,    83,
     180,    85,    86,    87,    88,    89,    90,    91,    92,   225,
     196,   195,    96,    97,    98,   149,   100,   101,    14,    -1,
      -1,   105,    -1,    19,    20,    -1,    22,    23,    -1,    -1,
     168,    -1,    -1,    29,    -1,    31,    32,    33,    -1,    -1,
      36,    -1,    38,   239,    -1,    -1,    42,    43,    -1,    -1,
      -1,    -1,    48,    -1,   238,    51,    -1,    -1,    54,    -1,
      -1,    57,    -1,    -1,    60,    61,    62,    -1,    64,    65,
      -1,    67,    68,    -1,    70,    -1,    -1,    73,    -1,    -1,
      76,    77,    78,    79,    80,    -1,    82,    83,    -1,    85,
      86,    87,    88,    89,    90,    91,    92,    -1,    -1,    -1,
      96,    97,    98,    -1,   100,   101,    -1,    -1,    -1,   105,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    55,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    14,    15,    16,    17,    71,    72,    -1,
      -1,    75,    -1,    -1,    -1,    -1,    27,    81,    -1,    30,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    -1,    -1,    -1,    45,    46,    47,    -1,   102,    -1,
     104,   105,    53,    -1,    55,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    14,    15,    16,    17,
      71,    72,    -1,    -1,    75,    -1,    -1,    -1,    -1,    27,
      81,    -1,    30,    84,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    -1,    -1,    -1,    45,    46,    47,
      -1,   102,    -1,   104,   105,    53,    -1,    55,    -1,    -1,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    14,
      15,    16,    17,    71,    72,    -1,    -1,    75,    -1,    -1,
      -1,    -1,    27,    81,    -1,    30,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    -1,    -1,    -1,   104,   105,    53,    -1,
      55,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    14,    15,    16,    17,    71,    72,    -1,    -1,
      75,    -1,    -1,    -1,    -1,    27,    81,    -1,    30,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    46,    47,    -1,    -1,    -1,   104,
     105,    53,    -1,    55,    -1,    -1,    58,    -1,    -1,    -1,
      -1,    63,    -1,    -1,    66,    -1,    -1,    -1,    -1,    71,
      72,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   105
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   115,   116,     0,    17,   107,   117,   120,   121,   192,
      14,    16,   195,    73,   100,   108,   118,    24,    34,   122,
      18,    38,    43,    97,    98,    14,    15,    27,    30,    45,
      46,    47,    53,    55,    58,    66,    71,    72,    75,    81,
      84,   104,   105,   120,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   158,   159,   160,   161,   164,   166,
     167,   168,   169,   170,   172,   173,   174,   175,   176,   178,
     179,   192,    14,    17,    19,    20,    22,    23,    29,    31,
      32,    33,    34,    36,    38,    42,    43,    48,    51,    54,
      57,    60,    61,    62,    64,    65,    67,    68,    70,    73,
      76,    77,    78,    79,    80,    82,    83,    85,    86,    87,
      88,    89,    90,    91,    92,    96,    97,    98,   100,   101,
     105,   123,   124,   125,   134,   196,    14,    15,    16,   180,
     177,    31,    92,   152,   189,   177,   108,   180,   188,    44,
     181,   144,    16,   157,   193,   195,    49,    50,    63,   103,
     195,   124,    20,    29,    68,    89,   127,   135,   118,   180,
      37,   144,   180,   182,    41,    13,   112,   113,   141,   102,
     108,   194,    14,    15,    16,   162,   163,   163,   142,   171,
     189,    18,    49,    89,    32,   136,    59,    14,    15,    16,
     153,   154,   156,    39,   118,   102,   183,   184,   190,   188,
     187,   171,    56,    90,   165,    41,    63,   145,   192,    14,
      15,   133,   126,    28,   137,   109,   118,   141,   144,   185,
     186,   195,   184,     9,    56,    63,   171,   108,   109,   119,
     110,   129,    14,    15,    69,   138,   154,   155,    74,    94,
      22,   193,   130,   131,   134,    49,    60,   132,    71,    14,
      24,    34,    35,   108,   109,   139,   140,   141,   186,   142,
     191,   108,   109,   111,   136,   128,   171,   131
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 366 "src/gram.y"
    {
						pltsql_parse_result = (PLTSQL_stmt_block *) (yyvsp[(2) - (3)].stmt);
					}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 376 "src/gram.y"
    {
						pltsql_DumpExecTree = true;
					}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 380 "src/gram.y"
    {
						pltsql_curr_compile->resolve_option = PLTSQL_RESOLVE_ERROR;
					}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 384 "src/gram.y"
    {
						pltsql_curr_compile->resolve_option = PLTSQL_RESOLVE_VARIABLE;
					}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 388 "src/gram.y"
    {
						pltsql_curr_compile->resolve_option = PLTSQL_RESOLVE_COLUMN;
					}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 403 "src/gram.y"
    {
						PLTSQL_stmt_block *new;
						int				  tok1;
						int				  tok2;
						char			  *label;

						new = palloc0(sizeof(PLTSQL_stmt_block));

						new->cmd_type	= PLTSQL_STMT_BLOCK;
						new->lineno		= pltsql_location_to_lineno((yylsp[(2) - (5)]));
						new->label		= (yyvsp[(1) - (5)].declhdr).label;
						new->n_initvars = (yyvsp[(1) - (5)].declhdr).n_initvars;
						new->initvarnos = (yyvsp[(1) - (5)].declhdr).initvarnos;
						new->body		= (yyvsp[(3) - (5)].list);
						new->exceptions	= (yyvsp[(4) - (5)].exception_block);

						pltsql_peek2(&tok1, &tok2, NULL, NULL);

						if (tok1 == IDENT && tok2 == ';')
						{
							tok1 = yylex();
							label = yylval.word.ident;
							check_labels((yyvsp[(1) - (5)].declhdr).label, label, yylloc);
							tok2 = yylex(); /* consume optional semicolon */
						}
						else if (tok1 == ';')
						{
							tok1 = yylex(); /* consume optional semicolon */
						}

						pltsql_ns_pop();

						(yyval.stmt) = (PLTSQL_stmt *)new;
					}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 440 "src/gram.y"
    {
						/* done with decls, so resume identifier lookup */
						pltsql_IdentifierLookup = IDENTIFIER_LOOKUP_NORMAL;
						(yyval.declhdr).label	  = (yyvsp[(1) - (1)].str);
						(yyval.declhdr).n_initvars = 0;
						(yyval.declhdr).initvarnos = NULL;
					}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 448 "src/gram.y"
    {
						pltsql_IdentifierLookup = IDENTIFIER_LOOKUP_NORMAL;
						(yyval.declhdr).label	  = (yyvsp[(1) - (2)].str);
						(yyval.declhdr).n_initvars = 0;
						(yyval.declhdr).initvarnos = NULL;
					}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 455 "src/gram.y"
    {
						pltsql_IdentifierLookup = IDENTIFIER_LOOKUP_NORMAL;
						(yyval.declhdr).label	  = (yyvsp[(1) - (3)].str);
						/* Remember variables declared in decl_stmts */
						(yyval.declhdr).n_initvars = pltsql_add_initdatums(&((yyval.declhdr).initvarnos));
					}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 464 "src/gram.y"
    {
						/* Forget any variables created before block */
						pltsql_add_initdatums(NULL);
						/*
						 * Disable scanner lookup of identifiers while
						 * we process the decl_stmts
						 */
						pltsql_IdentifierLookup = IDENTIFIER_LOOKUP_DECLARE;
					}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 481 "src/gram.y"
    {
						/* We allow useless extra DECLAREs */
					}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 485 "src/gram.y"
    {
						/*
						 * Throw a helpful error if user tries to put block
						 * label just before BEGIN, instead of before DECLARE.
						 */
						ereport(ERROR,
								(errcode(ERRCODE_SYNTAX_ERROR),
								 errmsg("block label must be placed before DECLARE, not after"),
								 parser_errposition((yylsp[(1) - (3)]))));
					}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 498 "src/gram.y"
    {
						PLTSQL_variable	*var;

						/*
						 * If a collation is supplied, insert it into the
						 * datatype.  We assume decl_datatype always returns
						 * a freshly built struct not shared with other
						 * variables.
						 */
						if (OidIsValid((yyvsp[(4) - (6)].oid)))
						{
							if (!OidIsValid((yyvsp[(3) - (6)].dtype)->collation))
								ereport(ERROR,
										(errcode(ERRCODE_DATATYPE_MISMATCH),
										 errmsg("collations are not supported by type %s",
												format_type_be((yyvsp[(3) - (6)].dtype)->typoid)),
										 parser_errposition((yylsp[(4) - (6)]))));
							(yyvsp[(3) - (6)].dtype)->collation = (yyvsp[(4) - (6)].oid);
						}

						var = pltsql_build_variable((yyvsp[(1) - (6)].varname).name, (yyvsp[(1) - (6)].varname).lineno,
													 (yyvsp[(3) - (6)].dtype), true);
						if ((yyvsp[(2) - (6)].boolean))
						{
							if (var->dtype == PLTSQL_DTYPE_VAR)
								((PLTSQL_var *) var)->isconst = (yyvsp[(2) - (6)].boolean);
							else
								ereport(ERROR,
										(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
										 errmsg("row or record variable cannot be CONSTANT"),
										 parser_errposition((yylsp[(2) - (6)]))));
						}
						if ((yyvsp[(5) - (6)].boolean))
						{
							if (var->dtype == PLTSQL_DTYPE_VAR)
								((PLTSQL_var *) var)->notnull = (yyvsp[(5) - (6)].boolean);
							else
								ereport(ERROR,
										(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
										 errmsg("row or record variable cannot be NOT NULL"),
										 parser_errposition((yylsp[(4) - (6)]))));

						}
						if ((yyvsp[(6) - (6)].expr) != NULL)
						{
							if (var->dtype == PLTSQL_DTYPE_VAR)
								((PLTSQL_var *) var)->default_val = (yyvsp[(6) - (6)].expr);
							else
								ereport(ERROR,
										(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
										 errmsg("default value for row or record variable is not supported"),
										 parser_errposition((yylsp[(5) - (6)]))));
						}
					}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 553 "src/gram.y"
    {
						pltsql_ns_additem((yyvsp[(4) - (5)].nsitem)->itemtype,
										   (yyvsp[(4) - (5)].nsitem)->itemno, (yyvsp[(1) - (5)].varname).name);
					}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 558 "src/gram.y"
    { pltsql_ns_push((yyvsp[(1) - (3)].varname).name); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 560 "src/gram.y"
    {
						PLTSQL_var *new;
						PLTSQL_expr *curname_def;
						char		buf[1024];
						char		*cp1;
						char		*cp2;

						/* pop local namespace for cursor args */
						pltsql_ns_pop();

						new = (PLTSQL_var *)
							pltsql_build_variable((yyvsp[(1) - (7)].varname).name, (yyvsp[(1) - (7)].varname).lineno,
												   pltsql_build_datatype(REFCURSOROID,
																		  -1,
																		  InvalidOid),
												   true);

						curname_def = palloc0(sizeof(PLTSQL_expr));

						curname_def->dtype = PLTSQL_DTYPE_EXPR;
						strcpy(buf, "SELECT ");
						cp1 = new->refname;
						cp2 = buf + strlen(buf);
						/*
						 * Don't trust standard_conforming_strings here;
						 * it might change before we use the string.
						 */
						if (strchr(cp1, '\\') != NULL)
							*cp2++ = ESCAPE_STRING_SYNTAX;
						*cp2++ = '\'';
						while (*cp1)
						{
							if (SQL_STR_DOUBLE(*cp1, true))
								*cp2++ = *cp1;
							*cp2++ = *cp1++;
						}
						strcpy(cp2, "'::pg_catalog.refcursor");
						curname_def->query = pstrdup(buf);
						new->default_val = curname_def;

						new->cursor_explicit_expr = (yyvsp[(7) - (7)].expr);
						if ((yyvsp[(5) - (7)].datum) == NULL)
							new->cursor_explicit_argrow = -1;
						else
							new->cursor_explicit_argrow = (yyvsp[(5) - (7)].datum)->dno;
						new->cursor_options = CURSOR_OPT_FAST_PLAN | (yyvsp[(2) - (7)].ival);
					}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 610 "src/gram.y"
    {
						(yyval.ival) = 0;
					}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 614 "src/gram.y"
    {
						(yyval.ival) = CURSOR_OPT_NO_SCROLL;
					}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 618 "src/gram.y"
    {
						(yyval.ival) = CURSOR_OPT_SCROLL;
					}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 624 "src/gram.y"
    {
						(yyval.expr) = read_sql_stmt_bos("");
					}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 630 "src/gram.y"
    {
						(yyval.datum) = NULL;
					}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 634 "src/gram.y"
    {
						PLTSQL_row *new;
						int i;
						ListCell *l;

						new = palloc0(sizeof(PLTSQL_row));
						new->dtype = PLTSQL_DTYPE_ROW;
						new->lineno = pltsql_location_to_lineno((yylsp[(1) - (3)]));
						new->rowtupdesc = NULL;
						new->nfields = list_length((yyvsp[(2) - (3)].list));
						new->fieldnames = palloc(new->nfields * sizeof(char *));
						new->varnos = palloc(new->nfields * sizeof(int));

						i = 0;
						foreach (l, (yyvsp[(2) - (3)].list))
						{
							PLTSQL_variable *arg = (PLTSQL_variable *) lfirst(l);
							new->fieldnames[i] = arg->refname;
							new->varnos[i] = arg->dno;
							i++;
						}
						list_free((yyvsp[(2) - (3)].list));

						pltsql_adddatum((PLTSQL_datum *) new);
						(yyval.datum) = (PLTSQL_datum *) new;
					}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 663 "src/gram.y"
    {
						(yyval.list) = list_make1((yyvsp[(1) - (1)].datum));
					}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 667 "src/gram.y"
    {
						(yyval.list) = lappend((yyvsp[(1) - (3)].list), (yyvsp[(3) - (3)].datum));
					}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 673 "src/gram.y"
    {
						(yyval.datum) = (PLTSQL_datum *)
							pltsql_build_variable((yyvsp[(1) - (2)].varname).name, (yyvsp[(1) - (2)].varname).lineno,
												   (yyvsp[(2) - (2)].dtype), true);
					}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 684 "src/gram.y"
    {
						PLTSQL_nsitem *nsi;

						nsi = pltsql_ns_lookup(pltsql_ns_top(), false,
												(yyvsp[(1) - (1)].word).ident, NULL, NULL,
												NULL);
						if (nsi == NULL)
							ereport(ERROR,
									(errcode(ERRCODE_UNDEFINED_OBJECT),
									 errmsg("variable \"%s\" does not exist",
											(yyvsp[(1) - (1)].word).ident),
									 parser_errposition((yylsp[(1) - (1)]))));
						(yyval.nsitem) = nsi;
					}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 699 "src/gram.y"
    {
						PLTSQL_nsitem *nsi;

						if (list_length((yyvsp[(1) - (1)].cword).idents) == 2)
							nsi = pltsql_ns_lookup(pltsql_ns_top(), false,
													strVal(linitial((yyvsp[(1) - (1)].cword).idents)),
													strVal(lsecond((yyvsp[(1) - (1)].cword).idents)),
													NULL,
													NULL);
						else if (list_length((yyvsp[(1) - (1)].cword).idents) == 3)
							nsi = pltsql_ns_lookup(pltsql_ns_top(), false,
													strVal(linitial((yyvsp[(1) - (1)].cword).idents)),
													strVal(lsecond((yyvsp[(1) - (1)].cword).idents)),
													strVal(lthird((yyvsp[(1) - (1)].cword).idents)),
													NULL);
						else
							nsi = NULL;
						if (nsi == NULL)
							ereport(ERROR,
									(errcode(ERRCODE_UNDEFINED_OBJECT),
									 errmsg("variable \"%s\" does not exist",
											NameListToString((yyvsp[(1) - (1)].cword).idents)),
									 parser_errposition((yylsp[(1) - (1)]))));
						(yyval.nsitem) = nsi;
					}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 727 "src/gram.y"
    {
						(yyval.varname).name = (yyvsp[(1) - (1)].word).ident;
						(yyval.varname).lineno = pltsql_location_to_lineno((yylsp[(1) - (1)]));
						/*
						 * Check to make sure name isn't already declared
						 * in the current block.
						 */
						if (pltsql_ns_lookup(pltsql_ns_top(), true,
											  (yyvsp[(1) - (1)].word).ident, NULL, NULL,
											  NULL) != NULL)
							yyerror("duplicate declaration");
					}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 740 "src/gram.y"
    {
						(yyval.varname).name = pstrdup((yyvsp[(1) - (1)].keyword));
						(yyval.varname).lineno = pltsql_location_to_lineno((yylsp[(1) - (1)]));
						/*
						 * Check to make sure name isn't already declared
						 * in the current block.
						 */
						if (pltsql_ns_lookup(pltsql_ns_top(), true,
											  (yyvsp[(1) - (1)].keyword), NULL, NULL,
											  NULL) != NULL)
							yyerror("duplicate declaration");
					}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 755 "src/gram.y"
    { (yyval.boolean) = false; }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 757 "src/gram.y"
    { (yyval.boolean) = true; }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 761 "src/gram.y"
    {
						/*
						 * If there's a lookahead token, read_datatype
						 * should consume it.
						 */
						(yyval.dtype) = read_datatype(yychar);
						yyclearin;
					}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 772 "src/gram.y"
    { (yyval.oid) = InvalidOid; }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 774 "src/gram.y"
    {
						(yyval.oid) = get_collation_oid(list_make1(makeString((yyvsp[(2) - (2)].word).ident)),
											   false);
					}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 779 "src/gram.y"
    {
						(yyval.oid) = get_collation_oid((yyvsp[(2) - (2)].cword).idents, false);
					}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 785 "src/gram.y"
    { (yyval.boolean) = false; }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 787 "src/gram.y"
    { (yyval.boolean) = true; }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 791 "src/gram.y"
    { (yyval.expr) = NULL; }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 793 "src/gram.y"
    { (yyval.expr) = NULL; }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 795 "src/gram.y"
    {
                        pltsql_push_back_token(K_DECLARE);
                        (yyval.expr) = NULL;
                    }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 800 "src/gram.y"
    {
                        pltsql_push_back_token(K_BEGIN);
                        (yyval.expr) = NULL;
                    }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 805 "src/gram.y"
    {
                        pltsql_push_back_token(T_WORD);
                        (yyval.expr) = NULL;
                    }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 810 "src/gram.y"
    {
						(yyval.expr) = read_sql_expression2_bos(';', ',', ", or ;", NULL);
					}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 824 "src/gram.y"
    { (yyval.list) = NIL; }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 826 "src/gram.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 830 "src/gram.y"
    {
							if ((yyvsp[(2) - (2)].stmt) == NULL)
								(yyval.list) = (yyvsp[(1) - (2)].list);
							else
								(yyval.list) = lappend((yyvsp[(1) - (2)].list), (yyvsp[(2) - (2)].stmt));
						}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 837 "src/gram.y"
    {
							if ((yyvsp[(1) - (1)].stmt) == NULL)
								(yyval.list) = NIL;
							else
								(yyval.list) = list_make1((yyvsp[(1) - (1)].stmt));
						}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 851 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 853 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 855 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 857 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 859 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 861 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 863 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 865 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 867 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 869 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 871 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 873 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 875 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 877 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 879 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 881 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 883 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 885 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 888 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 892 "src/gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 896 "src/gram.y"
    {
						PLTSQL_stmt_perform *new;

						new = palloc0(sizeof(PLTSQL_stmt_perform));
						new->cmd_type = PLTSQL_STMT_PERFORM;
						new->lineno   = pltsql_location_to_lineno((yylsp[(1) - (2)]));
						new->expr  = (yyvsp[(2) - (2)].expr);

						(yyval.stmt) = (PLTSQL_stmt *)new;
					}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 914 "src/gram.y"
    {
						PLTSQL_stmt_assign *new;

						new = palloc0(sizeof(PLTSQL_stmt_assign));
						new->cmd_type = PLTSQL_STMT_ASSIGN;
						new->lineno   = pltsql_location_to_lineno((yylsp[(2) - (4)]));
						new->varno = (yyvsp[(2) - (4)].ival);
						new->expr  = (yyvsp[(4) - (4)].expr);

						(yyval.stmt) = (PLTSQL_stmt *)new;
					}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 928 "src/gram.y"
    {
						PLTSQL_stmt_getdiag	 *new;
						ListCell		*lc;

						new = palloc0(sizeof(PLTSQL_stmt_getdiag));
						new->cmd_type = PLTSQL_STMT_GETDIAG;
						new->lineno   = pltsql_location_to_lineno((yylsp[(1) - (5)]));
						new->is_stacked = (yyvsp[(2) - (5)].boolean);
						new->diag_items = (yyvsp[(4) - (5)].list);

						/*
						 * Check information items are valid for area option.
						 */
						foreach(lc, new->diag_items)
						{
							PLTSQL_diag_item *ditem = (PLTSQL_diag_item *) lfirst(lc);

							switch (ditem->kind)
							{
								/* these fields are disallowed in stacked case */
								case PLTSQL_GETDIAG_ROW_COUNT:
								case PLTSQL_GETDIAG_RESULT_OID:
									if (new->is_stacked)
										ereport(ERROR,
												(errcode(ERRCODE_SYNTAX_ERROR),
												 errmsg("diagnostics item %s is not allowed in GET STACKED DIAGNOSTICS",
														pltsql_getdiag_kindname(ditem->kind)),
												 parser_errposition((yylsp[(1) - (5)]))));
									break;
								/* these fields are disallowed in current case */
								case PLTSQL_GETDIAG_ERROR_CONTEXT:
								case PLTSQL_GETDIAG_ERROR_DETAIL:
								case PLTSQL_GETDIAG_ERROR_HINT:
								case PLTSQL_GETDIAG_RETURNED_SQLSTATE:
								case PLTSQL_GETDIAG_MESSAGE_TEXT:
									if (!new->is_stacked)
										ereport(ERROR,
												(errcode(ERRCODE_SYNTAX_ERROR),
												 errmsg("diagnostics item %s is not allowed in GET CURRENT DIAGNOSTICS",
														pltsql_getdiag_kindname(ditem->kind)),
												 parser_errposition((yylsp[(1) - (5)]))));
									break;
								default:
									elog(ERROR, "unrecognized diagnostic item kind: %d",
										 ditem->kind);
									break;
							}
						}

						(yyval.stmt) = (PLTSQL_stmt *)new;
					}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 982 "src/gram.y"
    {
						(yyval.boolean) = false;
					}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 986 "src/gram.y"
    {
						(yyval.boolean) = false;
					}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 990 "src/gram.y"
    {
						(yyval.boolean) = true;
					}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 996 "src/gram.y"
    {
						(yyval.list) = lappend((yyvsp[(1) - (3)].list), (yyvsp[(3) - (3)].diagitem));
					}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 1000 "src/gram.y"
    {
						(yyval.list) = list_make1((yyvsp[(1) - (1)].diagitem));
					}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1006 "src/gram.y"
    {
						PLTSQL_diag_item *new;

						new = palloc(sizeof(PLTSQL_diag_item));
						new->target = (yyvsp[(1) - (3)].ival);
						new->kind = (yyvsp[(3) - (3)].ival);

						(yyval.diagitem) = new;
					}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 1018 "src/gram.y"
    {
						int	tok = yylex();

						if (tok_is_keyword(tok, &yylval,
										   K_ROW_COUNT, "row_count"))
							(yyval.ival) = PLTSQL_GETDIAG_ROW_COUNT;
						else if (tok_is_keyword(tok, &yylval,
												K_RESULT_OID, "result_oid"))
							(yyval.ival) = PLTSQL_GETDIAG_RESULT_OID;
						else if (tok_is_keyword(tok, &yylval,
												K_PG_EXCEPTION_DETAIL, "pg_exception_detail"))
							(yyval.ival) = PLTSQL_GETDIAG_ERROR_DETAIL;
						else if (tok_is_keyword(tok, &yylval,
												K_PG_EXCEPTION_HINT, "pg_exception_hint"))
							(yyval.ival) = PLTSQL_GETDIAG_ERROR_HINT;
						else if (tok_is_keyword(tok, &yylval,
												K_PG_EXCEPTION_CONTEXT, "pg_exception_context"))
							(yyval.ival) = PLTSQL_GETDIAG_ERROR_CONTEXT;
						else if (tok_is_keyword(tok, &yylval,
												K_MESSAGE_TEXT, "message_text"))
							(yyval.ival) = PLTSQL_GETDIAG_MESSAGE_TEXT;
						else if (tok_is_keyword(tok, &yylval,
												K_RETURNED_SQLSTATE, "returned_sqlstate"))
							(yyval.ival) = PLTSQL_GETDIAG_RETURNED_SQLSTATE;
						else
							yyerror("unrecognized GET DIAGNOSTICS item");
					}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1048 "src/gram.y"
    {
						check_assignable((yyvsp[(1) - (1)].wdatum).datum, (yylsp[(1) - (1)]));
						if ((yyvsp[(1) - (1)].wdatum).datum->dtype == PLTSQL_DTYPE_ROW ||
							(yyvsp[(1) - (1)].wdatum).datum->dtype == PLTSQL_DTYPE_REC)
							ereport(ERROR,
									(errcode(ERRCODE_SYNTAX_ERROR),
									 errmsg("\"%s\" is not a scalar variable",
											NameOfDatum(&((yyvsp[(1) - (1)].wdatum)))),
									 parser_errposition((yylsp[(1) - (1)]))));
						(yyval.ival) = (yyvsp[(1) - (1)].wdatum).datum->dno;
					}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 1060 "src/gram.y"
    {
						/* just to give a better message than "syntax error" */
						word_is_not_variable(&((yyvsp[(1) - (1)].word)), (yylsp[(1) - (1)]));
					}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1065 "src/gram.y"
    {
						/* just to give a better message than "syntax error" */
						cword_is_not_variable(&((yyvsp[(1) - (1)].cword)), (yylsp[(1) - (1)]));
					}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1073 "src/gram.y"
    {
						check_assignable((yyvsp[(1) - (1)].wdatum).datum, (yylsp[(1) - (1)]));
						(yyval.ival) = (yyvsp[(1) - (1)].wdatum).datum->dno;
					}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1078 "src/gram.y"
    {
						PLTSQL_arrayelem	*new;

						new = palloc0(sizeof(PLTSQL_arrayelem));
						new->dtype		= PLTSQL_DTYPE_ARRAYELEM;
						new->subscript	= (yyvsp[(3) - (3)].expr);
						new->arrayparentno = (yyvsp[(1) - (3)].ival);
						/* initialize cached type data to "not valid" */
						new->parenttypoid = InvalidOid;

						pltsql_adddatum((PLTSQL_datum *) new);

						(yyval.ival) = new->dno;
					}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1095 "src/gram.y"
    {
						PLTSQL_stmt_if *new;

						new = palloc0(sizeof(PLTSQL_stmt_if));
						new->cmd_type	= PLTSQL_STMT_IF;
						new->lineno		= pltsql_location_to_lineno((yylsp[(1) - (3)]));
						new->cond		= (yyvsp[(2) - (3)].expr);
						new->then_body	= list_make1((yyvsp[(3) - (3)].stmt));

						(yyval.stmt) = (PLTSQL_stmt *)new;
				}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1107 "src/gram.y"
    {
						PLTSQL_stmt_if *new;

						new = palloc0(sizeof(PLTSQL_stmt_if));
						new->cmd_type	= PLTSQL_STMT_IF;
						new->lineno		= pltsql_location_to_lineno((yylsp[(1) - (5)]));
						new->cond		= (yyvsp[(2) - (5)].expr);
						new->then_body	= list_make1((yyvsp[(3) - (5)].stmt));
						new->else_body  = list_make1((yyvsp[(5) - (5)].stmt));

						(yyval.stmt) = (PLTSQL_stmt *)new;
				}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1122 "src/gram.y"
    {
						PLTSQL_stmt_loop *new;

						new = palloc0(sizeof(PLTSQL_stmt_loop));
						new->cmd_type = PLTSQL_STMT_LOOP;
						new->lineno   = pltsql_location_to_lineno((yylsp[(2) - (3)]));
						new->label	  = (yyvsp[(1) - (3)].str);
						new->body	  = (yyvsp[(3) - (3)].loop_body).stmts;

						check_labels((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].loop_body).end_label, (yyvsp[(3) - (3)].loop_body).end_label_location);
						pltsql_ns_pop();

						(yyval.stmt) = (PLTSQL_stmt *)new;
					}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1139 "src/gram.y"
    {
						PLTSQL_stmt_while *new;

						new = palloc0(sizeof(PLTSQL_stmt_while));
						new->cmd_type = PLTSQL_STMT_WHILE;
						new->lineno   = pltsql_location_to_lineno((yylsp[(2) - (5)]));
						new->label	  = (yyvsp[(1) - (5)].str);
						new->cond	  = (yyvsp[(3) - (5)].expr);
						new->body	  = (yyvsp[(5) - (5)].loop_body).stmts;

						check_labels((yyvsp[(1) - (5)].str), (yyvsp[(5) - (5)].loop_body).end_label, (yyvsp[(5) - (5)].loop_body).end_label_location);
						pltsql_ns_pop();

						(yyval.stmt) = (PLTSQL_stmt *)new;
					}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1155 "src/gram.y"
    {
						PLTSQL_stmt_while *new;

						new = palloc0(sizeof(PLTSQL_stmt_while));
						new->cmd_type = PLTSQL_STMT_WHILE;
						new->lineno   = pltsql_location_to_lineno((yylsp[(2) - (4)]));
						new->label	  = (yyvsp[(1) - (4)].str);
						new->cond	  = (yyvsp[(3) - (4)].expr);
						new->body	  = list_make1((yyvsp[(4) - (4)].stmt));

						pltsql_ns_pop();

						(yyval.stmt) = (PLTSQL_stmt *)new;
					}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1174 "src/gram.y"
    {
						/* This runs after we've scanned the loop body */
						if ((yyvsp[(3) - (4)].stmt)->cmd_type == PLTSQL_STMT_FORI)
						{
							PLTSQL_stmt_fori		*new;

							new = (PLTSQL_stmt_fori *) (yyvsp[(3) - (4)].stmt);
							new->lineno   = pltsql_location_to_lineno((yylsp[(2) - (4)]));
							new->label	  = (yyvsp[(1) - (4)].str);
							new->body	  = (yyvsp[(4) - (4)].loop_body).stmts;
							(yyval.stmt) = (PLTSQL_stmt *) new;
						}
						else
						{
							PLTSQL_stmt_forq		*new;

							Assert((yyvsp[(3) - (4)].stmt)->cmd_type == PLTSQL_STMT_FORS ||
								   (yyvsp[(3) - (4)].stmt)->cmd_type == PLTSQL_STMT_FORC ||
								   (yyvsp[(3) - (4)].stmt)->cmd_type == PLTSQL_STMT_DYNFORS);
							/* forq is the common supertype of all three */
							new = (PLTSQL_stmt_forq *) (yyvsp[(3) - (4)].stmt);
							new->lineno   = pltsql_location_to_lineno((yylsp[(2) - (4)]));
							new->label	  = (yyvsp[(1) - (4)].str);
							new->body	  = (yyvsp[(4) - (4)].loop_body).stmts;
							(yyval.stmt) = (PLTSQL_stmt *) new;
						}

						check_labels((yyvsp[(1) - (4)].str), (yyvsp[(4) - (4)].loop_body).end_label, (yyvsp[(4) - (4)].loop_body).end_label_location);
						/* close namespace started in opt_block_label */
						pltsql_ns_pop();
					}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 1208 "src/gram.y"
    {
						int			tok = yylex();
						int			tokloc = yylloc;

						if (tok == K_EXECUTE)
						{
							/* EXECUTE means it's a dynamic FOR loop */
							PLTSQL_stmt_dynfors	*new;
							PLTSQL_expr			*expr;
							int						term;

							expr = read_sql_expression2(K_LOOP, K_USING,
														"LOOP or USING",
														&term);

							new = palloc0(sizeof(PLTSQL_stmt_dynfors));
							new->cmd_type = PLTSQL_STMT_DYNFORS;
							if ((yyvsp[(1) - (2)].forvariable).rec)
							{
								new->rec = (yyvsp[(1) - (2)].forvariable).rec;
								check_assignable((PLTSQL_datum *) new->rec, (yylsp[(1) - (2)]));
							}
							else if ((yyvsp[(1) - (2)].forvariable).row)
							{
								new->row = (yyvsp[(1) - (2)].forvariable).row;
								check_assignable((PLTSQL_datum *) new->row, (yylsp[(1) - (2)]));
							}
							else if ((yyvsp[(1) - (2)].forvariable).scalar)
							{
								/* convert single scalar to list */
								new->row = make_scalar_list1((yyvsp[(1) - (2)].forvariable).name, (yyvsp[(1) - (2)].forvariable).scalar,
															 (yyvsp[(1) - (2)].forvariable).lineno, (yylsp[(1) - (2)]));
								/* no need for check_assignable */
							}
							else
							{
								ereport(ERROR,
										(errcode(ERRCODE_DATATYPE_MISMATCH),
										 errmsg("loop variable of loop over rows must be a record or row variable or list of scalar variables"),
										 parser_errposition((yylsp[(1) - (2)]))));
							}
							new->query = expr;

							if (term == K_USING)
							{
								do
								{
									expr = read_sql_expression2(',', K_LOOP,
																", or LOOP",
																&term);
									new->params = lappend(new->params, expr);
								} while (term == ',');
							}

							(yyval.stmt) = (PLTSQL_stmt *) new;
						}
						else if (tok == T_DATUM &&
								 yylval.wdatum.datum->dtype == PLTSQL_DTYPE_VAR &&
								 ((PLTSQL_var *) yylval.wdatum.datum)->datatype->typoid == REFCURSOROID)
						{
							/* It's FOR var IN cursor */
							PLTSQL_stmt_forc	*new;
							PLTSQL_var			*cursor = (PLTSQL_var *) yylval.wdatum.datum;

							new = (PLTSQL_stmt_forc *) palloc0(sizeof(PLTSQL_stmt_forc));
							new->cmd_type = PLTSQL_STMT_FORC;
							new->curvar = cursor->dno;

							/* Should have had a single variable name */
							if ((yyvsp[(1) - (2)].forvariable).scalar && (yyvsp[(1) - (2)].forvariable).row)
								ereport(ERROR,
										(errcode(ERRCODE_SYNTAX_ERROR),
										 errmsg("cursor FOR loop must have only one target variable"),
										 parser_errposition((yylsp[(1) - (2)]))));

							/* can't use an unbound cursor this way */
							if (cursor->cursor_explicit_expr == NULL)
								ereport(ERROR,
										(errcode(ERRCODE_SYNTAX_ERROR),
										 errmsg("cursor FOR loop must use a bound cursor variable"),
										 parser_errposition(tokloc)));

							/* collect cursor's parameters if any */
							new->argquery = read_cursor_args(cursor,
															 K_LOOP,
															 "LOOP");

							/* create loop's private RECORD variable */
							new->rec = pltsql_build_record((yyvsp[(1) - (2)].forvariable).name,
															(yyvsp[(1) - (2)].forvariable).lineno,
															true);

							(yyval.stmt) = (PLTSQL_stmt *) new;
						}
						else
						{
							PLTSQL_expr	*expr1;
							int				expr1loc;
							bool			reverse = false;

							/*
							 * We have to distinguish between two
							 * alternatives: FOR var IN a .. b and FOR
							 * var IN query. Unfortunately this is
							 * tricky, since the query in the second
							 * form needn't start with a SELECT
							 * keyword.  We use the ugly hack of
							 * looking for two periods after the first
							 * token. We also check for the REVERSE
							 * keyword, which means it must be an
							 * integer loop.
							 */
							if (tok_is_keyword(tok, &yylval,
											   K_REVERSE, "reverse"))
								reverse = true;
							else
								pltsql_push_back_token(tok);

							/*
							 * Read tokens until we see either a ".."
							 * or a LOOP. The text we read may not
							 * necessarily be a well-formed SQL
							 * statement, so we need to invoke
							 * read_sql_construct directly.
							 */
							expr1 = read_sql_construct(DOT_DOT,
													   K_LOOP,
													   0,
													   "LOOP",
													   "SELECT ",
													   true,
													   false,
													   true,
													   &expr1loc,
													   &tok);

							if (tok == DOT_DOT)
							{
								/* Saw "..", so it must be an integer loop */
								PLTSQL_expr		*expr2;
								PLTSQL_expr		*expr_by;
								PLTSQL_var			*fvar;
								PLTSQL_stmt_fori	*new;

								/* Check first expression is well-formed */
								check_sql_expr(expr1->query, expr1loc, 7);

								/* Read and check the second one */
								expr2 = read_sql_expression2(K_LOOP, K_BY,
															 "LOOP",
															 &tok);

								/* Get the BY clause if any */
								if (tok == K_BY)
									expr_by = read_sql_expression(K_LOOP,
																  "LOOP");
								else
									expr_by = NULL;

								/* Should have had a single variable name */
								if ((yyvsp[(1) - (2)].forvariable).scalar && (yyvsp[(1) - (2)].forvariable).row)
									ereport(ERROR,
											(errcode(ERRCODE_SYNTAX_ERROR),
											 errmsg("integer FOR loop must have only one target variable"),
											 parser_errposition((yylsp[(1) - (2)]))));

								/* create loop's private variable */
								fvar = (PLTSQL_var *)
									pltsql_build_variable((yyvsp[(1) - (2)].forvariable).name,
														   (yyvsp[(1) - (2)].forvariable).lineno,
														   pltsql_build_datatype(INT4OID,
																				  -1,
																				  InvalidOid),
														   true);

								new = palloc0(sizeof(PLTSQL_stmt_fori));
								new->cmd_type = PLTSQL_STMT_FORI;
								new->var	  = fvar;
								new->reverse  = reverse;
								new->lower	  = expr1;
								new->upper	  = expr2;
								new->step	  = expr_by;

								(yyval.stmt) = (PLTSQL_stmt *) new;
							}
							else
							{
								/*
								 * No "..", so it must be a query loop. We've
								 * prefixed an extra SELECT to the query text,
								 * so we need to remove that before performing
								 * syntax checking.
								 */
								char				*tmp_query;
								PLTSQL_stmt_fors	*new;

								if (reverse)
									ereport(ERROR,
											(errcode(ERRCODE_SYNTAX_ERROR),
											 errmsg("cannot specify REVERSE in query FOR loop"),
											 parser_errposition(tokloc)));

								Assert(strncmp(expr1->query, "SELECT ", 7) == 0);
								tmp_query = pstrdup(expr1->query + 7);
								pfree(expr1->query);
								expr1->query = tmp_query;

								check_sql_expr(expr1->query, expr1loc, 0);

								new = palloc0(sizeof(PLTSQL_stmt_fors));
								new->cmd_type = PLTSQL_STMT_FORS;
								if ((yyvsp[(1) - (2)].forvariable).rec)
								{
									new->rec = (yyvsp[(1) - (2)].forvariable).rec;
									check_assignable((PLTSQL_datum *) new->rec, (yylsp[(1) - (2)]));
								}
								else if ((yyvsp[(1) - (2)].forvariable).row)
								{
									new->row = (yyvsp[(1) - (2)].forvariable).row;
									check_assignable((PLTSQL_datum *) new->row, (yylsp[(1) - (2)]));
								}
								else if ((yyvsp[(1) - (2)].forvariable).scalar)
								{
									/* convert single scalar to list */
									new->row = make_scalar_list1((yyvsp[(1) - (2)].forvariable).name, (yyvsp[(1) - (2)].forvariable).scalar,
																 (yyvsp[(1) - (2)].forvariable).lineno, (yylsp[(1) - (2)]));
									/* no need for check_assignable */
								}
								else
								{
									ereport(ERROR,
											(errcode(ERRCODE_SYNTAX_ERROR),
											 errmsg("loop variable of loop over rows must be a record or row variable or list of scalar variables"),
											 parser_errposition((yylsp[(1) - (2)]))));
								}

								new->query = expr1;
								(yyval.stmt) = (PLTSQL_stmt *) new;
							}
						}
					}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1470 "src/gram.y"
    {
						(yyval.forvariable).name = NameOfDatum(&((yyvsp[(1) - (1)].wdatum)));
						(yyval.forvariable).lineno = pltsql_location_to_lineno((yylsp[(1) - (1)]));
						if ((yyvsp[(1) - (1)].wdatum).datum->dtype == PLTSQL_DTYPE_ROW)
						{
							(yyval.forvariable).scalar = NULL;
							(yyval.forvariable).rec = NULL;
							(yyval.forvariable).row = (PLTSQL_row *) (yyvsp[(1) - (1)].wdatum).datum;
						}
						else if ((yyvsp[(1) - (1)].wdatum).datum->dtype == PLTSQL_DTYPE_REC)
						{
							(yyval.forvariable).scalar = NULL;
							(yyval.forvariable).rec = (PLTSQL_rec *) (yyvsp[(1) - (1)].wdatum).datum;
							(yyval.forvariable).row = NULL;
						}
						else
						{
							int			tok;

							(yyval.forvariable).scalar = (yyvsp[(1) - (1)].wdatum).datum;
							(yyval.forvariable).rec = NULL;
							(yyval.forvariable).row = NULL;
							/* check for comma-separated list */
							tok = yylex();
							pltsql_push_back_token(tok);
							if (tok == ',')
								(yyval.forvariable).row = read_into_scalar_list((yyval.forvariable).name,
															   (yyval.forvariable).scalar,
															   (yylsp[(1) - (1)]));
						}
					}
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 1502 "src/gram.y"
    {
						int			tok;

						(yyval.forvariable).name = (yyvsp[(1) - (1)].word).ident;
						(yyval.forvariable).lineno = pltsql_location_to_lineno((yylsp[(1) - (1)]));
						(yyval.forvariable).scalar = NULL;
						(yyval.forvariable).rec = NULL;
						(yyval.forvariable).row = NULL;
						/* check for comma-separated list */
						tok = yylex();
						pltsql_push_back_token(tok);
						if (tok == ',')
							word_is_not_variable(&((yyvsp[(1) - (1)].word)), (yylsp[(1) - (1)]));
					}
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1517 "src/gram.y"
    {
						/* just to give a better message than "syntax error" */
						cword_is_not_variable(&((yyvsp[(1) - (1)].cword)), (yylsp[(1) - (1)]));
					}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 1524 "src/gram.y"
    {
						PLTSQL_stmt_foreach_a *new;

						new = palloc0(sizeof(PLTSQL_stmt_foreach_a));
						new->cmd_type = PLTSQL_STMT_FOREACH_A;
						new->lineno = pltsql_location_to_lineno((yylsp[(2) - (8)]));
						new->label = (yyvsp[(1) - (8)].str);
						new->slice = (yyvsp[(4) - (8)].ival);
						new->expr = (yyvsp[(7) - (8)].expr);
						new->body = (yyvsp[(8) - (8)].loop_body).stmts;

						if ((yyvsp[(3) - (8)].forvariable).rec)
						{
							new->varno = (yyvsp[(3) - (8)].forvariable).rec->dno;
							check_assignable((PLTSQL_datum *) (yyvsp[(3) - (8)].forvariable).rec, (yylsp[(3) - (8)]));
						}
						else if ((yyvsp[(3) - (8)].forvariable).row)
						{
							new->varno = (yyvsp[(3) - (8)].forvariable).row->dno;
							check_assignable((PLTSQL_datum *) (yyvsp[(3) - (8)].forvariable).row, (yylsp[(3) - (8)]));
						}
						else if ((yyvsp[(3) - (8)].forvariable).scalar)
						{
							new->varno = (yyvsp[(3) - (8)].forvariable).scalar->dno;
							check_assignable((yyvsp[(3) - (8)].forvariable).scalar, (yylsp[(3) - (8)]));
						}
						else
						{
							ereport(ERROR,
									(errcode(ERRCODE_SYNTAX_ERROR),
									 errmsg("loop variable of FOREACH must be a known variable or list of variables"),
											 parser_errposition((yylsp[(3) - (8)]))));
						}

						check_labels((yyvsp[(1) - (8)].str), (yyvsp[(8) - (8)].loop_body).end_label, (yyvsp[(8) - (8)].loop_body).end_label_location);
						pltsql_ns_pop();

						(yyval.stmt) = (PLTSQL_stmt *) new;
					}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 1566 "src/gram.y"
    {
						(yyval.ival) = 0;
					}
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 1570 "src/gram.y"
    {
						(yyval.ival) = (yyvsp[(2) - (2)].ival);
					}
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1576 "src/gram.y"
    {
						PLTSQL_stmt_exit *new;

						new = palloc0(sizeof(PLTSQL_stmt_exit));
						new->cmd_type = PLTSQL_STMT_EXIT;
						new->is_exit  = (yyvsp[(1) - (3)].boolean);
						new->lineno	  = pltsql_location_to_lineno((yylsp[(1) - (3)]));
						new->label	  = (yyvsp[(2) - (3)].str);
						new->cond	  = (yyvsp[(3) - (3)].expr);

						(yyval.stmt) = (PLTSQL_stmt *)new;
					}
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 1591 "src/gram.y"
    {
						(yyval.boolean) = true;
					}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 1595 "src/gram.y"
    {
						(yyval.boolean) = false;
					}
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 1601 "src/gram.y"
    {
						int	tok;

						tok = yylex();
						if (tok == 0)
							yyerror("unexpected end of function definition");

						if (tok_is_keyword(tok, &yylval,
										   K_NEXT, "next"))
						{
							(yyval.stmt) = make_return_next_stmt((yylsp[(1) - (1)]));
						}
						else if (tok_is_keyword(tok, &yylval,
												K_QUERY, "query"))
						{
							(yyval.stmt) = make_return_query_stmt((yylsp[(1) - (1)]));
						}
						else
						{
							pltsql_push_back_token(tok);
							(yyval.stmt) = make_return_stmt((yylsp[(1) - (1)]));
						}
					}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 1627 "src/gram.y"
    {
						PLTSQL_stmt_raise		*new;
						int	tok;

						new = palloc(sizeof(PLTSQL_stmt_raise));

						new->cmd_type	= PLTSQL_STMT_RAISE;
						new->lineno		= pltsql_location_to_lineno((yylsp[(1) - (1)]));
						new->elog_level = ERROR;	/* default */
						new->condname	= NULL;
						new->message	= NULL;
						new->params		= NIL;
						new->options	= NIL;

						tok = yylex();
						if (tok == 0)
							yyerror("unexpected end of function definition");

						/*
						 * We could have just RAISE, meaning to re-throw
						 * the current error.
						 */
						if (tok != ';')
						{
							/*
							 * First is an optional elog severity level.
							 */
							if (tok_is_keyword(tok, &yylval,
											   K_EXCEPTION, "exception"))
							{
								new->elog_level = ERROR;
								tok = yylex();
							}
							else if (tok_is_keyword(tok, &yylval,
													K_WARNING, "warning"))
							{
								new->elog_level = WARNING;
								tok = yylex();
							}
							else if (tok_is_keyword(tok, &yylval,
													K_NOTICE, "notice"))
							{
								new->elog_level = NOTICE;
								tok = yylex();
							}
							else if (tok_is_keyword(tok, &yylval,
													K_INFO, "info"))
							{
								new->elog_level = INFO;
								tok = yylex();
							}
							else if (tok_is_keyword(tok, &yylval,
													K_LOG, "log"))
							{
								new->elog_level = LOG;
								tok = yylex();
							}
							else if (tok_is_keyword(tok, &yylval,
													K_DEBUG, "debug"))
							{
								new->elog_level = DEBUG1;
								tok = yylex();
							}
							if (tok == 0)
								yyerror("unexpected end of function definition");

							/*
							 * Next we can have a condition name, or
							 * equivalently SQLSTATE 'xxxxx', or a string
							 * literal that is the old-style message format,
							 * or USING to start the option list immediately.
							 */
							if (tok == SCONST)
							{
								/* old style message and parameters */
								new->message = yylval.str;
								/*
								 * We expect either a semi-colon, which
								 * indicates no parameters, or a comma that
								 * begins the list of parameter expressions,
								 * or USING to begin the options list.
								 */
								tok = yylex();
								if (tok != ',' && tok != ';' && tok != K_USING)
									yyerror("syntax error");

								while (tok == ',')
								{
									PLTSQL_expr *expr;

									expr = read_sql_construct(',', ';', K_USING,
															  ", or ; or USING",
															  "SELECT ",
															  true, true, true,
															  NULL, &tok);
									new->params = lappend(new->params, expr);
								}
							}
							else if (tok != K_USING)
							{
								/* must be condition name or SQLSTATE */
								if (tok_is_keyword(tok, &yylval,
												   K_SQLSTATE, "sqlstate"))
								{
									/* next token should be a string literal */
									char   *sqlstatestr;

									if (yylex() != SCONST)
										yyerror("syntax error");
									sqlstatestr = yylval.str;

									if (strlen(sqlstatestr) != 5)
										yyerror("invalid SQLSTATE code");
									if (strspn(sqlstatestr, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ") != 5)
										yyerror("invalid SQLSTATE code");
									new->condname = sqlstatestr;
								}
								else
								{
									if (tok != T_WORD)
										yyerror("syntax error");
									new->condname = yylval.word.ident;
									pltsql_recognize_err_condition(new->condname,
																	false);
								}
								tok = yylex();
								if (tok != ';' && tok != K_USING)
									yyerror("syntax error");
							}

							if (tok == K_USING)
								new->options = read_raise_options();
						}

						(yyval.stmt) = (PLTSQL_stmt *)new;
					}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 1766 "src/gram.y"
    {
						PLTSQL_stmt_raise		*new;
						int	tok;
						PLTSQL_expr *expr;

						new = palloc(sizeof(PLTSQL_stmt_raise));

						new->cmd_type	= PLTSQL_STMT_RAISE;
						new->lineno		= pltsql_location_to_lineno((yylsp[(1) - (1)]));
						/*
						 * Of all the message levels that are usually visible to
						 * clients, INFO is the least likely to be configured to
						 * show up in the server logs.
						 */
						new->elog_level = INFO;
						new->condname	= NULL;
						new->message	= NULL;
						new->params		= NIL;
						new->options	= NIL;

						tok = yylex();
						if (tok == 0)
							yyerror("unexpected end of function definition");

						if (tok == ';')
							yyerror("Incorrect syntax");

						/*
						 * We expect only one parameter: either a string
						 * literal, a local variable or a global variable.
						 */
						if (tok == SCONST)
							new->message = yylval.str;
						else if (tok == T_DATUM)
						{
							pltsql_push_back_token(tok);

							new->message = "%";
							expr = read_sql_construct_bos(';', 0, 0,
													  " ",
													  "SELECT ",
													  true, true, true,
													  NULL, &tok, true);
							new->params = lappend(new->params, expr);
						}

						/*
						 * Make semicolon statement termination optional.
						 */
						tok = yylex();
						if (tok != ';')
						   pltsql_push_back_token(tok);

						(yyval.stmt) = (PLTSQL_stmt *)new;
					}
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 1824 "src/gram.y"
    {
						(yyval.loop_body).stmts = (yyvsp[(1) - (5)].list);
						(yyval.loop_body).end_label = (yyvsp[(4) - (5)].str);
						(yyval.loop_body).end_label_location = (yylsp[(4) - (5)]);
					}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1842 "src/gram.y"
    {
						(yyval.stmt) = make_execsql_stmt(K_INSERT, (yylsp[(1) - (1)]), NULL);
					}
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1846 "src/gram.y"
    {
						int			tok;

						tok = yylex();
						pltsql_push_back_token(tok);
						if (tok == '=' || tok == COLON_EQUALS || tok == '[')
							word_is_not_variable(&((yyvsp[(1) - (1)].word)), (yylsp[(1) - (1)]));
						(yyval.stmt) = make_execsql_stmt(T_WORD, (yylsp[(1) - (1)]), &((yyvsp[(1) - (1)].word)));
					}
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 1856 "src/gram.y"
    {
						int			tok;

						tok = yylex();
						pltsql_push_back_token(tok);
						if (tok == '=' || tok == COLON_EQUALS || tok == '[')
							cword_is_not_variable(&((yyvsp[(1) - (1)].cword)), (yylsp[(1) - (1)]));
						(yyval.stmt) = make_execsql_stmt(T_CWORD, (yylsp[(1) - (1)]), NULL);
					}
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 1868 "src/gram.y"
    {
						PLTSQL_stmt_dynexecute *new;
						PLTSQL_expr *expr;
						int endtoken;

						expr = read_sql_construct(K_INTO, K_USING, ';',
												  "INTO or USING or ;",
												  "SELECT ",
												  true, true, true,
												  NULL, &endtoken);

						new = palloc(sizeof(PLTSQL_stmt_dynexecute));
						new->cmd_type = PLTSQL_STMT_DYNEXECUTE;
						new->lineno = pltsql_location_to_lineno((yylsp[(1) - (1)]));
						new->query = expr;
						new->into = false;
						new->strict = false;
						new->rec = NULL;
						new->row = NULL;
						new->params = NIL;

						/*
						 * We loop to allow the INTO and USING clauses to
						 * appear in either order, since people easily get
						 * that wrong.  This coding also prevents "INTO foo"
						 * from getting absorbed into a USING expression,
						 * which is *really* confusing.
						 */
						for (;;)
						{
							if (endtoken == K_INTO)
							{
								if (new->into)			/* multiple INTO */
									yyerror("syntax error");
								new->into = true;
								read_into_target(&new->rec, &new->row, &new->strict);
								endtoken = yylex();
							}
							else if (endtoken == K_USING)
							{
								if (new->params)		/* multiple USING */
									yyerror("syntax error");
								do
								{
									expr = read_sql_construct(',', ';', K_INTO,
															  ", or ; or INTO",
															  "SELECT ",
															  true, true, true,
															  NULL, &endtoken);
									new->params = lappend(new->params, expr);
								} while (endtoken == ',');
							}
							else if (endtoken == ';')
								break;
							else
								yyerror("syntax error");
						}

						(yyval.stmt) = (PLTSQL_stmt *)new;
					}
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 1932 "src/gram.y"
    {
						PLTSQL_stmt_open *new;
						int				  tok;

						new = palloc0(sizeof(PLTSQL_stmt_open));
						new->cmd_type = PLTSQL_STMT_OPEN;
						new->lineno = pltsql_location_to_lineno((yylsp[(1) - (2)]));
						new->curvar = (yyvsp[(2) - (2)].var)->dno;
						new->cursor_options = CURSOR_OPT_FAST_PLAN;

						if ((yyvsp[(2) - (2)].var)->cursor_explicit_expr == NULL)
						{
							/* be nice if we could use opt_scrollable here */
							tok = yylex();
							if (tok_is_keyword(tok, &yylval,
											   K_NO, "no"))
							{
								tok = yylex();
								if (tok_is_keyword(tok, &yylval,
												   K_SCROLL, "scroll"))
								{
									new->cursor_options |= CURSOR_OPT_NO_SCROLL;
									tok = yylex();
								}
							}
							else if (tok_is_keyword(tok, &yylval,
													K_SCROLL, "scroll"))
							{
								new->cursor_options |= CURSOR_OPT_SCROLL;
								tok = yylex();
							}

							if (tok != K_FOR)
								yyerror("syntax error, expected \"FOR\"");

							tok = yylex();
							if (tok == K_EXECUTE)
							{
								int		endtoken;

								new->dynquery =
									read_sql_expression2(K_USING, ';',
														 "USING or ;",
														 &endtoken);

								/* If we found "USING", collect argument(s) */
								if (endtoken == K_USING)
								{
									PLTSQL_expr *expr;

									do
									{
										expr = read_sql_expression2(',', ';',
																	", or ;",
																	&endtoken);
										new->params = lappend(new->params,
															  expr);
									} while (endtoken == ',');
								}
							}
							else
							{
								pltsql_push_back_token(tok);
								new->query = read_sql_stmt("");
							}
						}
						else
						{
							/* predefined cursor query, so read args */
							new->argquery = read_cursor_args((yyvsp[(2) - (2)].var), ';', ";");
						}

						(yyval.stmt) = (PLTSQL_stmt *)new;
					}
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 2009 "src/gram.y"
    {
						PLTSQL_stmt_fetch *fetch = (yyvsp[(2) - (4)].fetch);
						PLTSQL_rec	   *rec;
						PLTSQL_row	   *row;

						/* We have already parsed everything through the INTO keyword */
						read_into_target(&rec, &row, NULL);

						if (yylex() != ';')
							yyerror("syntax error");

						/*
						 * We don't allow multiple rows in PL/TSQL's FETCH
						 * statement, only in MOVE.
						 */
						if (fetch->returns_multiple_rows)
							ereport(ERROR,
									(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
									 errmsg("FETCH statement cannot return multiple rows"),
									 parser_errposition((yylsp[(1) - (4)]))));

						fetch->lineno = pltsql_location_to_lineno((yylsp[(1) - (4)]));
						fetch->rec		= rec;
						fetch->row		= row;
						fetch->curvar	= (yyvsp[(3) - (4)].var)->dno;
						fetch->is_move	= false;

						(yyval.stmt) = (PLTSQL_stmt *)fetch;
					}
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 2041 "src/gram.y"
    {
						PLTSQL_stmt_fetch *fetch = (yyvsp[(2) - (4)].fetch);

						fetch->lineno = pltsql_location_to_lineno((yylsp[(1) - (4)]));
						fetch->curvar	= (yyvsp[(3) - (4)].var)->dno;
						fetch->is_move	= true;

						(yyval.stmt) = (PLTSQL_stmt *)fetch;
					}
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 2053 "src/gram.y"
    {
						(yyval.fetch) = read_fetch_direction();
					}
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 2059 "src/gram.y"
    {
						PLTSQL_stmt_close *new;

						new = palloc(sizeof(PLTSQL_stmt_close));
						new->cmd_type = PLTSQL_STMT_CLOSE;
						new->lineno = pltsql_location_to_lineno((yylsp[(1) - (3)]));
						new->curvar = (yyvsp[(2) - (3)].var)->dno;

						(yyval.stmt) = (PLTSQL_stmt *)new;
					}
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 2072 "src/gram.y"
    {
						/* We do not bother building a node for NULL */
						(yyval.stmt) = NULL;
					}
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 2079 "src/gram.y"
    {
						if ((yyvsp[(1) - (1)].wdatum).datum->dtype != PLTSQL_DTYPE_VAR)
							ereport(ERROR,
									(errcode(ERRCODE_DATATYPE_MISMATCH),
									 errmsg("cursor variable must be a simple variable"),
									 parser_errposition((yylsp[(1) - (1)]))));

						if (((PLTSQL_var *) (yyvsp[(1) - (1)].wdatum).datum)->datatype->typoid != REFCURSOROID)
							ereport(ERROR,
									(errcode(ERRCODE_DATATYPE_MISMATCH),
									 errmsg("variable \"%s\" must be of type cursor or refcursor",
											((PLTSQL_var *) (yyvsp[(1) - (1)].wdatum).datum)->refname),
									 parser_errposition((yylsp[(1) - (1)]))));
						(yyval.var) = (PLTSQL_var *) (yyvsp[(1) - (1)].wdatum).datum;
					}
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 2095 "src/gram.y"
    {
						/* just to give a better message than "syntax error" */
						word_is_not_variable(&((yyvsp[(1) - (1)].word)), (yylsp[(1) - (1)]));
					}
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 2100 "src/gram.y"
    {
						/* just to give a better message than "syntax error" */
						cword_is_not_variable(&((yyvsp[(1) - (1)].cword)), (yylsp[(1) - (1)]));
					}
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 2107 "src/gram.y"
    { (yyval.exception_block) = NULL; }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 2109 "src/gram.y"
    {
						/*
						 * We use a mid-rule action to add these
						 * special variables to the namespace before
						 * parsing the WHEN clauses themselves.  The
						 * scope of the names extends to the end of the
						 * current block.
						 */
						int			lineno = pltsql_location_to_lineno((yylsp[(1) - (1)]));
						PLTSQL_exception_block *new = palloc(sizeof(PLTSQL_exception_block));
						PLTSQL_variable *var;

						var = pltsql_build_variable("sqlstate", lineno,
													 pltsql_build_datatype(TEXTOID,
																			-1,
																			pltsql_curr_compile->fn_input_collation),
													 true);
						((PLTSQL_var *) var)->isconst = true;
						new->sqlstate_varno = var->dno;

						var = pltsql_build_variable("sqlerrm", lineno,
													 pltsql_build_datatype(TEXTOID,
																			-1,
																			pltsql_curr_compile->fn_input_collation),
													 true);
						((PLTSQL_var *) var)->isconst = true;
						new->sqlerrm_varno = var->dno;

						(yyval.exception_block) = new;
					}
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 2140 "src/gram.y"
    {
						PLTSQL_exception_block *new = (yyvsp[(2) - (3)].exception_block);
						new->exc_list = (yyvsp[(3) - (3)].list);

						(yyval.exception_block) = new;
					}
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 2149 "src/gram.y"
    {
							(yyval.list) = lappend((yyvsp[(1) - (2)].list), (yyvsp[(2) - (2)].exception));
						}
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 2153 "src/gram.y"
    {
							(yyval.list) = list_make1((yyvsp[(1) - (1)].exception));
						}
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 2159 "src/gram.y"
    {
						PLTSQL_exception *new;

						new = palloc0(sizeof(PLTSQL_exception));
						new->lineno = pltsql_location_to_lineno((yylsp[(1) - (4)]));
						new->conditions = (yyvsp[(2) - (4)].condition);
						new->action = (yyvsp[(4) - (4)].list);

						(yyval.exception) = new;
					}
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 2172 "src/gram.y"
    {
							PLTSQL_condition	*old;

							for (old = (yyvsp[(1) - (3)].condition); old->next != NULL; old = old->next)
								/* skip */ ;
							old->next = (yyvsp[(3) - (3)].condition);
							(yyval.condition) = (yyvsp[(1) - (3)].condition);
						}
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 2181 "src/gram.y"
    {
							(yyval.condition) = (yyvsp[(1) - (1)].condition);
						}
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 2187 "src/gram.y"
    {
							if (strcmp((yyvsp[(1) - (1)].str), "sqlstate") != 0)
							{
								(yyval.condition) = pltsql_parse_err_condition((yyvsp[(1) - (1)].str));
							}
							else
							{
								PLTSQL_condition *new;
								char   *sqlstatestr;

								/* next token should be a string literal */
								if (yylex() != SCONST)
									yyerror("syntax error");
								sqlstatestr = yylval.str;

								if (strlen(sqlstatestr) != 5)
									yyerror("invalid SQLSTATE code");
								if (strspn(sqlstatestr, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ") != 5)
									yyerror("invalid SQLSTATE code");

								new = palloc(sizeof(PLTSQL_condition));
								new->sqlerrstate =
									MAKE_SQLSTATE(sqlstatestr[0],
												  sqlstatestr[1],
												  sqlstatestr[2],
												  sqlstatestr[3],
												  sqlstatestr[4]);
								new->condname = sqlstatestr;
								new->next = NULL;

								(yyval.condition) = new;
							}
						}
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 2223 "src/gram.y"
    { (yyval.expr) = read_sql_expression(';', ";"); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 2227 "src/gram.y"
    { (yyval.expr) = read_sql_expression_bos(';', ";"); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 2231 "src/gram.y"
    { (yyval.expr) = read_sql_expression_bos(0, ""); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 2235 "src/gram.y"
    { (yyval.expr) = read_sql_expression(']', "]"); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 2239 "src/gram.y"
    { (yyval.expr) = read_sql_expression(K_LOOP, "LOOP"); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 2243 "src/gram.y"
    {
						pltsql_ns_push(NULL);
						(yyval.str) = NULL;
					}
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 2248 "src/gram.y"
    {
						pltsql_ns_push((yyvsp[(2) - (3)].str));
						(yyval.str) = (yyvsp[(2) - (3)].str);
					}
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 2255 "src/gram.y"
    {
						(yyval.str) = NULL;
					}
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 2259 "src/gram.y"
    {
						if (pltsql_ns_lookup_label(pltsql_ns_top(), (yyvsp[(1) - (1)].str)) == NULL)
							yyerror("label does not exist");
						(yyval.str) = (yyvsp[(1) - (1)].str);
					}
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 2267 "src/gram.y"
    { (yyval.expr) = NULL; }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 2269 "src/gram.y"
    { (yyval.expr) = (yyvsp[(2) - (2)].expr); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 2276 "src/gram.y"
    {
						(yyval.str) = (yyvsp[(1) - (1)].word).ident;
					}
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 2280 "src/gram.y"
    {
						if ((yyvsp[(1) - (1)].wdatum).ident == NULL) /* composite name not OK */
							yyerror("syntax error");
						(yyval.str) = (yyvsp[(1) - (1)].wdatum).ident;
					}
    break;



/* Line 1806 of yacc.c  */
#line 4493 "src/pl_gram.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 2336 "src/gram.y"


/*
 * Check whether a token represents an "unreserved keyword".
 * We have various places where we want to recognize a keyword in preference
 * to a variable name, but not reserve that keyword in other contexts.
 * Hence, this kluge.
 */
static bool
tok_is_keyword(int token, union YYSTYPE *lval,
			   int kw_token, const char *kw_str)
{
	if (token == kw_token)
	{
		/* Normal case, was recognized by scanner (no conflicting variable) */
		return true;
	}
	else if (token == T_DATUM)
	{
		/*
		 * It's a variable, so recheck the string name.  Note we will not
		 * match composite names (hence an unreserved word followed by "."
		 * will not be recognized).
		 */
		if (!lval->wdatum.quoted && lval->wdatum.ident != NULL &&
			strcmp(lval->wdatum.ident, kw_str) == 0)
			return true;
	}
	return false;				/* not the keyword */
}

/*
 * Convenience routine to complain when we expected T_DATUM and got T_WORD,
 * ie, unrecognized variable.
 */
static void
word_is_not_variable(PLword *word, int location)
{
	ereport(ERROR,
			(errcode(ERRCODE_SYNTAX_ERROR),
			 errmsg("\"%s\" is not a known variable",
					word->ident),
			 parser_errposition(location)));
}

/* Same, for a CWORD */
static void
cword_is_not_variable(PLcword *cword, int location)
{
	ereport(ERROR,
			(errcode(ERRCODE_SYNTAX_ERROR),
			 errmsg("\"%s\" is not a known variable",
					NameListToString(cword->idents)),
			 parser_errposition(location)));
}

/*
 * Convenience routine to complain when we expected T_DATUM and got
 * something else.  "tok" must be the current token, since we also
 * look at yylval and yylloc.
 */
static void
current_token_is_not_variable(int tok)
{
	if (tok == T_WORD)
		word_is_not_variable(&(yylval.word), yylloc);
	else if (tok == T_CWORD)
		cword_is_not_variable(&(yylval.cword), yylloc);
	else
		yyerror("syntax error");
}

/* Convenience routine to read an expression with one possible terminator */
static PLTSQL_expr *
read_sql_expression(int until, const char *expected)
{
	return read_sql_construct(until, 0, 0, expected,
							  "SELECT ", true, true, true, NULL, NULL);
}

/* Convenience routine to read an expression with two possible terminators */
static PLTSQL_expr *
read_sql_expression2(int until, int until2, const char *expected,
					 int *endtoken)
{
	return read_sql_construct(until, until2, 0, expected,
							  "SELECT ", true, true, true, NULL, endtoken);
}

/*
 * Convenience routine to read an expression with an explicit or
 * beginning-of-statement token.
 */
static PLTSQL_expr *
read_sql_expression_bos(int until, const char *expected)
{
	return read_sql_construct_bos(until, 0, 0, expected,
							  "SELECT ", true, true, true, NULL, NULL, true);
}

/*
 * Convenience routine to read an expression with two possible explicit
 * terminators or a beginning-of-statement token.
 */
static PLTSQL_expr *
read_sql_expression2_bos(int until, int until2, const char *expected,
					 int *endtoken)
{
	return read_sql_construct_bos(until, until2, 0, expected,
							  "SELECT ", true, true, true, NULL, endtoken,
							  true);
}

/* Convenience routine to read a SQL statement that must end with ';' */
static PLTSQL_expr *
read_sql_stmt(const char *sqlstart)
{
	return read_sql_construct(';', 0, 0, ";",
                                  sqlstart, false, true, true, NULL, NULL);
}

/*
 * Convenience routine to read a SQL statement that must end with ';' or at
 * a beginning-of-statement token.
 */
static PLTSQL_expr *
read_sql_stmt_bos(const char *sqlstart)
{
	return read_sql_construct_bos(';', 0, 0, ";",
                                  sqlstart, false, true, true, NULL, NULL, true);
}

/*
 * Read a SQL construct and build a PLTSQL_expr for it.
 *
 * until:		token code for expected terminator
 * until2:		token code for alternate terminator (pass 0 if none)
 * until3:		token code for another alternate terminator (pass 0 if none)
 * expected:	text to use in complaining that terminator was not found
 * sqlstart:	text to prefix to the accumulated SQL text
 * isexpression: whether to say we're reading an "expression" or a "statement"
 * valid_sql:   whether to check the syntax of the expr (prefixed with sqlstart)
 * trim:		trim trailing whitespace
 * startloc:	if not NULL, location of first token is stored at *startloc
 * endtoken:	if not NULL, ending token is stored at *endtoken
 *				(this is only interesting if until2 or until3 isn't zero)
 */
static PLTSQL_expr *
read_sql_construct(int until,
				   int until2,
				   int until3,
				   const char *expected,
				   const char *sqlstart,
				   bool isexpression,
				   bool valid_sql,
				   bool trim,
				   int *startloc,
				   int *endtoken)
{
	return read_sql_construct_bos(until, until2, until3, expected, sqlstart,
							  isexpression, valid_sql, trim, startloc, endtoken,
							  false);
}

/*
 * Read a SQL construct and build a PLTSQL_expr for it, read until one of the
 * terminator tokens is encountered or optionally until the end of the line.
 *
 * until:		token code for expected terminator
 * until2:		token code for alternate terminator (pass 0 if none)
 * until3:		token code for another alternate terminator (pass 0 if none)
 * expected:	text to use in complaining that terminator was not found
 * sqlstart:	text to prefix to the accumulated SQL text
 * isexpression: whether to say we're reading an "expression" or a "statement"
 * valid_sql:   whether to check the syntax of the expr (prefixed with sqlstart)
 * trim:		trim trailing whitespace
 * startloc:	if not NULL, location of first token is stored at *startloc
 * endtoken:	if not NULL, ending token is stored at *endtoken
 *				(this is only interesting if until2 or until3 isn't zero)
 * untilbostok:	whether a beginning-of-statement token is a terminator
 */
static PLTSQL_expr *
read_sql_construct_bos(int until,
					   int until2,
					   int until3,
					   const char *expected,
					   const char *sqlstart,
					   bool isexpression,
					   bool valid_sql,
					   bool trim,
					   int *startloc,
					   int *endtoken,
					   bool untilbostok)
{
	int					tok;
	StringInfoData		ds;
	IdentifierLookup	save_IdentifierLookup;
	int					startlocation = -1;
	int					parenlevel = 0;
	int					sqlstartlen = strlen(sqlstart);
	PLTSQL_expr			*expr;
	List				*tsql_idents = NIL;

	initStringInfo(&ds);
	appendStringInfoString(&ds, sqlstart);

	/* special lookup mode for identifiers within the SQL text */
	save_IdentifierLookup = pltsql_IdentifierLookup;
	pltsql_IdentifierLookup = IDENTIFIER_LOOKUP_EXPR;

	for (;;)
	{
		tok = yylex();
		if (startlocation < 0)			/* remember loc of first token */
			startlocation = yylloc;
		if (tok == until && parenlevel == 0)
			break;
		if (tok == until2 && parenlevel == 0)
			break;
		if (tok == until3 && parenlevel == 0)
			break;
		if (untilbostok &&
		    is_terminator(tok,
		                  (startlocation == yylloc),
		                  startlocation, yylloc, sqlstart, tsql_idents) &&
		    parenlevel == 0)
		{
			pltsql_push_back_token(tok);
			break;
		}

		if (tok == '(' || tok == '[')
			parenlevel++;
		else if (tok == ')' || tok == ']')
		{
			parenlevel--;
			if (parenlevel < 0)
				yyerror("mismatched parentheses");
		}

		tsql_idents = append_if_tsql_identifier(tok, sqlstartlen, startlocation,
		                                     tsql_idents);

		/*
		 * End of function definition is an error, and we don't expect to
		 * hit a semicolon either (unless it's the until symbol, in which
		 * case we should have fallen out above).
		 */
		if (tok == 0 || tok == ';')
		{
			if (parenlevel != 0)
				yyerror("mismatched parentheses");
			if (isexpression)
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("missing \"%s\" at end of SQL expression",
								expected),
						 parser_errposition(yylloc)));
			else
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("missing \"%s\" at end of SQL statement",
								expected),
						 parser_errposition(yylloc)));
		}
	}

	pltsql_IdentifierLookup = save_IdentifierLookup;

	if (startloc)
		*startloc = startlocation;
	if (endtoken)
		*endtoken = tok;

	/* give helpful complaint about empty input */
	if (startlocation >= yylloc)
	{
		if (isexpression)
			yyerror("missing expression");
		else
			yyerror("missing SQL statement");
	}

	pltsql_append_source_text(&ds, startlocation, yylloc);

	/* trim any trailing whitespace, for neatness */
	if (trim)
	{
		while (ds.len > 0 && scanner_isspace(ds.data[ds.len - 1]))
			ds.data[--ds.len] = '\0';
	}

	expr = palloc0(sizeof(PLTSQL_expr));
	expr->dtype			= PLTSQL_DTYPE_EXPR;
	expr->query			= pstrdup(quote_tsql_identifiers(&ds, tsql_idents));
	expr->plan			= NULL;
	expr->paramnos		= NULL;
	expr->ns			= pltsql_ns_top();
	pfree(ds.data);

	if (valid_sql)
		check_sql_expr(expr->query, startlocation, strlen(sqlstart));
	return expr;
}

static List *
append_if_tsql_identifier(int tok, int start_len, int start_loc,
						List *tsql_idents)
{
	char				*ident;
	tsql_ident_ref		*tident_ref;
	int					tsql_ident_len;
	bool				is_ident_quoted;

	ident = NULL;
	
	if (tok == T_WORD)
	{
		ident = yylval.word.ident;
		is_ident_quoted = yylval.word.quoted;
	}
	else if (tok == T_DATUM)
	{
		ident = NameOfDatum(&(yylval.wdatum));
		is_ident_quoted = yylval.wdatum.quoted;
	}

	/*
	 * Create and append a reference to this word if it is a TSQL (at-prefixed)
	 * identifier.
	 */
	if (ident && !is_ident_quoted)
	{
		tsql_ident_len = strlen(ident);

		if (tsql_ident_len > 0 && (ident[0] == '@' || ident[0] == '#'))
		{
			tident_ref = palloc(sizeof(tsql_ident_ref));
			tident_ref->location = (start_len - 1) +
				(yylloc - start_loc);
			tident_ref->ident = pstrdup(ident);
			tsql_idents = lappend(tsql_idents, tident_ref);
		}
	}

	return tsql_idents;
}

static char *
quote_tsql_identifiers(const StringInfo src, const List *tsql_idents)
{
	StringInfoData	dest;
	ListCell		*lc;
	int				prev = 0;

	if (list_length(tsql_idents) == 0)
		return src->data;

	initStringInfo(&dest);

	foreach(lc, tsql_idents)
	{
		tsql_ident_ref *tword = (tsql_ident_ref *) lfirst(lc);

		/*
		 * Append the part of the source text appearing before the identifier
		 * that we haven't inserted already.
		 */
		appendBinaryStringInfo(&dest, &(src->data[prev]),
							   tword->location - prev + 1);
		appendStringInfo(&dest, "\"%s\"", tword->ident);
		prev = tword->location + 1 + strlen(tword->ident);
	}

	appendStringInfoString(&dest, &(src->data[prev]));
	return dest.data;
}

/*
 * Determines whether there the specified token is a statement terminator.
 *
 * "tok" must be the current token, since we also look at yylval.
 */
static bool
is_terminator(int tok, bool first, int start_loc, int cur_loc,
			  const char *sql_start, const List *tsql_idents)
{
	StringInfoData	ds;
	bool			validsql = true;
	MemoryContext	oldcontext = CurrentMemoryContext;

	switch (tok)
	{
		/* Ambiguous tokens not included: NULL */
		case ';':
		case K_BEGIN:
		case K_CLOSE:
		case K_DECLARE:
		case K_EXIT:
		case K_FETCH:
		case K_FOR:
		case K_FOREACH:
		case K_GET:
		case K_IF:
		case K_INSERT:
		case K_MOVE:
		case K_OPEN:
		case K_PERFORM:
		case K_PRINT:
		case K_RAISE:
		case K_RETURN:
		case K_SET:
		case K_WHILE:
		case LESS_LESS:			/* Optional label for many statements */
		/*
		 * These are not core TSQL statements but are needed to support dual
		 * syntax, in particular, the PL/pgSQL syntax for their respective
		 * statements.
		 */
		case K_LOOP:
			return true;
		/*
		 * We work harder in the ambiguous cases and perform a basic syntax
		 * analysis to guide us.
		 */
		case K_ELSE:			/* Ambiguous: CASE expr versus IF-ELSE stmt */
		case K_END:				/* Ambiguous: CASE expr versus block END */

			if (first)
				yyerror("syntax error");
			
			initStringInfo(&ds);
			
			if (sql_start)
				appendStringInfoString(&ds, sql_start);

			pltsql_append_source_text(&ds, start_loc, cur_loc);

			PG_TRY();
			{
				check_sql_expr(quote_tsql_identifiers(&ds, tsql_idents),
				               start_loc,
				               sql_start ? strlen(sql_start) : 0);
			}
			PG_CATCH();
			{
				MemoryContextSwitchTo(oldcontext);
				FlushErrorState();
				validsql = false;
			}
			PG_END_TRY();
			return validsql;
	}

	/* List of words that are not tokens but mark the beginning of a statement. */
	return word_matches(tok, "UPDATE") ||
		   word_matches(tok, "DELETE") ||
		   (!first && word_matches(tok, "SELECT"));
}

static bool
word_matches(int tok, const char *pattern)
{
	return ((tok == T_WORD) &&
	        (pg_strcasecmp(yylval.word.ident, pattern) == 0));
}

static PLTSQL_type *
read_datatype(int tok)
{
	StringInfoData		ds;
	char			   *type_name;
	int					startlocation;
	PLTSQL_type		*result;
	int					parenlevel = 0;
	bool				first = true;

	/* Should only be called while parsing DECLARE sections */
	Assert(pltsql_IdentifierLookup == IDENTIFIER_LOOKUP_DECLARE);

	/* Often there will be a lookahead token, but if not, get one */
	if (tok == YYEMPTY)
		tok = yylex();

	startlocation = yylloc;

	/*
	 * If we have a simple or composite identifier, check for %TYPE
	 * and %ROWTYPE constructs.
	 */
	if (tok == T_WORD)
	{
		char   *dtname = yylval.word.ident;

		tok = yylex();
		if (tok == '%')
		{
			tok = yylex();
			if (tok_is_keyword(tok, &yylval,
							   K_TYPE, "type"))
			{
				result = pltsql_parse_wordtype(dtname);
				if (result)
					return result;
			}
			else if (tok_is_keyword(tok, &yylval,
									K_ROWTYPE, "rowtype"))
			{
				result = pltsql_parse_wordrowtype(dtname);
				if (result)
					return result;
			}
		}
	}
	else if (tok == T_CWORD)
	{
		List   *dtnames = yylval.cword.idents;

		tok = yylex();
		if (tok == '%')
		{
			tok = yylex();
			if (tok_is_keyword(tok, &yylval,
							   K_TYPE, "type"))
			{
				result = pltsql_parse_cwordtype(dtnames);
				if (result)
					return result;
			}
			else if (tok_is_keyword(tok, &yylval,
									K_ROWTYPE, "rowtype"))
			{
				result = pltsql_parse_cwordrowtype(dtnames);
				if (result)
					return result;
			}
		}
	}

	while (tok != ';')
	{
		if (tok == 0)
		{
			if (parenlevel != 0)
				yyerror("mismatched parentheses");
			else
				yyerror("incomplete data type declaration");
		}
		/* Possible followers for datatype in a declaration */
		if (tok == K_COLLATE || tok == K_NOT ||
		    tok == '=' || tok == COLON_EQUALS || tok == K_DEFAULT)
			break;
		/* Possible followers for datatype in a cursor_arg list */
		if ((tok == ',' || tok == ')') && parenlevel == 0)
			break;
		if (tok == '(')
			parenlevel++;
		else if (tok == ')')
			parenlevel--;
		if (is_terminator(tok, first, startlocation, yylloc, NULL, NIL) &&
		    parenlevel == 0)
			break;

		tok = yylex();
		first = false;
	}

	/* set up ds to contain complete typename text */
	initStringInfo(&ds);
	pltsql_append_source_text(&ds, startlocation, yylloc);

	/* trim any trailing whitespace, for neatness */
	while (ds.len > 0 && scanner_isspace(ds.data[ds.len - 1]))
		ds.data[--ds.len] = '\0';

	type_name = ds.data;

	if (type_name[0] == '\0')
		yyerror("missing data type declaration");

	result = parse_datatype(type_name, startlocation);

	pfree(ds.data);

	pltsql_push_back_token(tok);

	return result;
}

static PLTSQL_stmt *
make_execsql_stmt(int firsttoken, int location, PLword *firstword)
{
	StringInfoData		ds;
	IdentifierLookup	save_IdentifierLookup;
	PLTSQL_stmt_execsql *execsql;
	PLTSQL_expr		*expr;
	PLTSQL_row			*row = NULL;
	PLTSQL_rec			*rec = NULL;
	int					tok;
	int					prev_tok;
	bool				have_into = false;
	bool				have_strict = false;
	bool				have_temptbl = false;
	bool				is_prev_tok_create = false;
	int					into_start_loc = -1;
	int					into_end_loc = -1;
	int					temptbl_loc = -1;
	List				*tsql_idents = NIL;

	initStringInfo(&ds);

	/* special lookup mode for identifiers within the SQL text */
	save_IdentifierLookup = pltsql_IdentifierLookup;
	pltsql_IdentifierLookup = IDENTIFIER_LOOKUP_EXPR;

	/*
	 * We have to special-case the sequence INSERT INTO, because we don't want
	 * that to be taken as an INTO-variables clause.  Fortunately, this is the
	 * only valid use of INTO in a pl/pgsql SQL command, and INTO is already a
	 * fully reserved word in the main grammar.  We have to treat it that way
	 * anywhere in the string, not only at the start; consider CREATE RULE
	 * containing an INSERT statement.
	 */
	tok = firsttoken;
	is_prev_tok_create =
		(firstword && (pg_strcasecmp(firstword->ident, "CREATE") == 0));
	for (;;)
	{
		prev_tok = tok;
		tok = yylex();
		if (have_into && into_end_loc < 0)
			into_end_loc = yylloc;		/* token after the INTO part */
		if (tok == ';')
			break;
		tsql_idents = append_if_tsql_identifier(tok,
		                                        (have_temptbl ?
		                                         strlen(TEMPOBJ_QUALIFIER) : 0),
		                                        location, tsql_idents);
		if (tok == 0)
			yyerror("unexpected end of function definition");

		if (tok == K_INTO && prev_tok != K_INSERT)
		{
			if (have_into)
				yyerror("INTO specified more than once");
			have_into = true;
			into_start_loc = yylloc;
			pltsql_IdentifierLookup = IDENTIFIER_LOOKUP_NORMAL;
			read_into_target(&rec, &row, &have_strict);
			pltsql_IdentifierLookup = IDENTIFIER_LOOKUP_EXPR;
		}
		/*
		 * We need to identify CREATE TABLE <#ident> as a local temporary table
		 * so we can translate it to a CREATE TEMPORARY TABLE statement later.
		 */
		if (is_prev_tok_create && word_matches(tok, "TABLE"))
		{
			temptbl_loc = yylloc;

			tok = yylex();
			if (tok == T_WORD && (!yylval.word.quoted) &&
			    (yylval.word.ident[0] == '#'))
				have_temptbl = true;

			pltsql_push_back_token(tok);
		}
		/* See the call to check_sql_expr below if you change this */
		is_prev_tok_create = false;
	}

	pltsql_IdentifierLookup = save_IdentifierLookup;

	if (have_into)
	{
		/*
		 * Insert an appropriate number of spaces corresponding to the
		 * INTO text, so that locations within the redacted SQL statement
		 * still line up with those in the original source text.
		 */
		pltsql_append_source_text(&ds, location, into_start_loc);
		appendStringInfoSpaces(&ds, into_end_loc - into_start_loc);
		pltsql_append_source_text(&ds, into_end_loc, yylloc);
	}
	else
	{
		if (have_temptbl)
		{
			/*
			 * We have a local temporary table identifier after the CREATE
			 * TABLE tokens, we need to transform CREATE TABLE -> CREATE
			 * TEMPORARY TABLE in this case.
			 */
			pltsql_append_source_text(&ds, location, temptbl_loc);
			appendStringInfoString(&ds, TEMPOBJ_QUALIFIER);
			pltsql_append_source_text(&ds, temptbl_loc, yylloc);
		}
		else
		{
			pltsql_append_source_text(&ds, location, yylloc);
		}
	}

	/* trim any trailing whitespace, for neatness */
	while (ds.len > 0 && scanner_isspace(ds.data[ds.len - 1]))
		ds.data[--ds.len] = '\0';

	expr = palloc0(sizeof(PLTSQL_expr));
	expr->dtype			= PLTSQL_DTYPE_EXPR;
	expr->query			= pstrdup(quote_tsql_identifiers(&ds, tsql_idents));
	expr->plan			= NULL;
	expr->paramnos		= NULL;
	expr->ns			= pltsql_ns_top();
	pfree(ds.data);

	/*
	 * If have_temptbl is true, the first two tokens were valid so we expect
	 * that check_sql_expr will raise errors from a location occurring after
	 * the TEMPORARY token.  Because the original statement did not include it,
	 * we offset the error location with its length so it points back to the
	 * correct location in the original source.
	 */
	check_sql_expr(expr->query, location, (have_temptbl ?
	                                       strlen(TEMPOBJ_QUALIFIER) : 0));

	execsql = palloc(sizeof(PLTSQL_stmt_execsql));
	execsql->cmd_type = PLTSQL_STMT_EXECSQL;
	execsql->lineno  = pltsql_location_to_lineno(location);
	execsql->sqlstmt = expr;
	execsql->into	 = have_into;
	execsql->strict	 = have_strict;
	execsql->rec	 = rec;
	execsql->row	 = row;

	return (PLTSQL_stmt *) execsql;
}


/*
 * Read FETCH or MOVE direction clause (everything through FROM/IN).
 */
static PLTSQL_stmt_fetch *
read_fetch_direction(void)
{
	PLTSQL_stmt_fetch *fetch;
	int			tok;
	bool		check_FROM = true;

	/*
	 * We create the PLTSQL_stmt_fetch struct here, but only fill in
	 * the fields arising from the optional direction clause
	 */
	fetch = (PLTSQL_stmt_fetch *) palloc0(sizeof(PLTSQL_stmt_fetch));
	fetch->cmd_type = PLTSQL_STMT_FETCH;
	/* set direction defaults: */
	fetch->direction = FETCH_FORWARD;
	fetch->how_many  = 1;
	fetch->expr		 = NULL;
	fetch->returns_multiple_rows = false;

	tok = yylex();
	if (tok == 0)
		yyerror("unexpected end of function definition");

	if (tok_is_keyword(tok, &yylval,
					   K_NEXT, "next"))
	{
		/* use defaults */
	}
	else if (tok_is_keyword(tok, &yylval,
							K_PRIOR, "prior"))
	{
		fetch->direction = FETCH_BACKWARD;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_FIRST, "first"))
	{
		fetch->direction = FETCH_ABSOLUTE;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_LAST, "last"))
	{
		fetch->direction = FETCH_ABSOLUTE;
		fetch->how_many  = -1;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_ABSOLUTE, "absolute"))
	{
		fetch->direction = FETCH_ABSOLUTE;
		fetch->expr = read_sql_expression2(K_FROM, K_IN,
										   "FROM or IN",
										   NULL);
		check_FROM = false;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_RELATIVE, "relative"))
	{
		fetch->direction = FETCH_RELATIVE;
		fetch->expr = read_sql_expression2(K_FROM, K_IN,
										   "FROM or IN",
										   NULL);
		check_FROM = false;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_ALL, "all"))
	{
		fetch->how_many = FETCH_ALL;
		fetch->returns_multiple_rows = true;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_FORWARD, "forward"))
	{
		complete_direction(fetch, &check_FROM);
	}
	else if (tok_is_keyword(tok, &yylval,
							K_BACKWARD, "backward"))
	{
		fetch->direction = FETCH_BACKWARD;
		complete_direction(fetch, &check_FROM);
	}
	else if (tok == K_FROM || tok == K_IN)
	{
		/* empty direction */
		check_FROM = false;
	}
	else if (tok == T_DATUM)
	{
		/* Assume there's no direction clause and tok is a cursor name */
		pltsql_push_back_token(tok);
		check_FROM = false;
	}
	else
	{
		/*
		 * Assume it's a count expression with no preceding keyword.
		 * Note: we allow this syntax because core SQL does, but we don't
		 * document it because of the ambiguity with the omitted-direction
		 * case.  For instance, "MOVE n IN c" will fail if n is a variable.
		 * Perhaps this can be improved someday, but it's hardly worth a
		 * lot of work.
		 */
		pltsql_push_back_token(tok);
		fetch->expr = read_sql_expression2(K_FROM, K_IN,
										   "FROM or IN",
										   NULL);
		fetch->returns_multiple_rows = true;
		check_FROM = false;
	}

	/* check FROM or IN keyword after direction's specification */
	if (check_FROM)
	{
		tok = yylex();
		if (tok != K_FROM && tok != K_IN)
			yyerror("expected FROM or IN");
	}

	return fetch;
}

/*
 * Process remainder of FETCH/MOVE direction after FORWARD or BACKWARD.
 * Allows these cases:
 *   FORWARD expr,  FORWARD ALL,  FORWARD
 *   BACKWARD expr, BACKWARD ALL, BACKWARD
 */
static void
complete_direction(PLTSQL_stmt_fetch *fetch,  bool *check_FROM)
{
	int			tok;

	tok = yylex();
	if (tok == 0)
		yyerror("unexpected end of function definition");

	if (tok == K_FROM || tok == K_IN)
	{
		*check_FROM = false;
		return;
	}

	if (tok == K_ALL)
	{
		fetch->how_many = FETCH_ALL;
		fetch->returns_multiple_rows = true;
		*check_FROM = true;
		return;
	}

	pltsql_push_back_token(tok);
	fetch->expr = read_sql_expression2(K_FROM, K_IN,
									   "FROM or IN",
									   NULL);
	fetch->returns_multiple_rows = true;
	*check_FROM = false;
}


static PLTSQL_stmt *
make_return_stmt(int location)
{
	PLTSQL_stmt_return *new;

	new = palloc0(sizeof(PLTSQL_stmt_return));
	new->cmd_type = PLTSQL_STMT_RETURN;
	new->lineno   = pltsql_location_to_lineno(location);
	new->expr	  = NULL;
	new->retvarno = -1;

	if (pltsql_curr_compile->fn_retset)
	{
		if (yylex() != ';')
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("RETURN cannot have a parameter in function returning set"),
					 errhint("Use RETURN NEXT or RETURN QUERY."),
					 parser_errposition(yylloc)));
	}
	else if (pltsql_curr_compile->out_param_varno >= 0)
	{
		if (yylex() != ';')
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("RETURN cannot have a parameter in function with OUT parameters"),
					 parser_errposition(yylloc)));
		new->retvarno = pltsql_curr_compile->out_param_varno;
	}
	else if (pltsql_curr_compile->fn_rettype == VOIDOID)
	{
		if (yylex() != ';')
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("RETURN cannot have a parameter in function returning void"),
					 parser_errposition(yylloc)));
	}
	else if (pltsql_curr_compile->fn_retistuple)
	{
		switch (yylex())
		{
			case K_NULL:
				/* we allow this to support RETURN NULL in triggers */
				break;

			case T_DATUM:
				if (yylval.wdatum.datum->dtype == PLTSQL_DTYPE_ROW ||
					yylval.wdatum.datum->dtype == PLTSQL_DTYPE_REC)
					new->retvarno = yylval.wdatum.datum->dno;
				else
					ereport(ERROR,
							(errcode(ERRCODE_DATATYPE_MISMATCH),
							 errmsg("RETURN must specify a record or row variable in function returning row"),
							 parser_errposition(yylloc)));
				break;

			default:
				ereport(ERROR,
						(errcode(ERRCODE_DATATYPE_MISMATCH),
						 errmsg("RETURN must specify a record or row variable in function returning row"),
						 parser_errposition(yylloc)));
				break;
		}
		if (yylex() != ';')
			yyerror("syntax error");
	}
	else
	{
		/*
		 * Note that a well-formed expression is _required_ here;
		 * anything else is a compile-time error.
		 */
		new->expr = read_sql_expression(';', ";");
	}

	return (PLTSQL_stmt *) new;
}


static PLTSQL_stmt *
make_return_next_stmt(int location)
{
	PLTSQL_stmt_return_next *new;

	if (!pltsql_curr_compile->fn_retset)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("cannot use RETURN NEXT in a non-SETOF function"),
				 parser_errposition(location)));

	new = palloc0(sizeof(PLTSQL_stmt_return_next));
	new->cmd_type	= PLTSQL_STMT_RETURN_NEXT;
	new->lineno		= pltsql_location_to_lineno(location);
	new->expr		= NULL;
	new->retvarno	= -1;

	if (pltsql_curr_compile->out_param_varno >= 0)
	{
		if (yylex() != ';')
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("RETURN NEXT cannot have a parameter in function with OUT parameters"),
					 parser_errposition(yylloc)));
		new->retvarno = pltsql_curr_compile->out_param_varno;
	}
	else if (pltsql_curr_compile->fn_retistuple)
	{
		switch (yylex())
		{
			case T_DATUM:
				if (yylval.wdatum.datum->dtype == PLTSQL_DTYPE_ROW ||
					yylval.wdatum.datum->dtype == PLTSQL_DTYPE_REC)
					new->retvarno = yylval.wdatum.datum->dno;
				else
					ereport(ERROR,
							(errcode(ERRCODE_DATATYPE_MISMATCH),
							 errmsg("RETURN NEXT must specify a record or row variable in function returning row"),
							 parser_errposition(yylloc)));
				break;

			default:
				ereport(ERROR,
						(errcode(ERRCODE_DATATYPE_MISMATCH),
						 errmsg("RETURN NEXT must specify a record or row variable in function returning row"),
						 parser_errposition(yylloc)));
				break;
		}
		if (yylex() != ';')
			yyerror("syntax error");
	}
	else
		new->expr = read_sql_expression(';', ";");

	return (PLTSQL_stmt *) new;
}


static PLTSQL_stmt *
make_return_query_stmt(int location)
{
	PLTSQL_stmt_return_query *new;
	int			tok;

	if (!pltsql_curr_compile->fn_retset)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("cannot use RETURN QUERY in a non-SETOF function"),
				 parser_errposition(location)));

	new = palloc0(sizeof(PLTSQL_stmt_return_query));
	new->cmd_type = PLTSQL_STMT_RETURN_QUERY;
	new->lineno = pltsql_location_to_lineno(location);

	/* check for RETURN QUERY EXECUTE */
	if ((tok = yylex()) != K_EXECUTE)
	{
		/* ordinary static query */
		pltsql_push_back_token(tok);
		new->query = read_sql_stmt("");
	}
	else
	{
		/* dynamic SQL */
		int		term;

		new->dynquery = read_sql_expression2(';', K_USING, "; or USING",
											 &term);
		if (term == K_USING)
		{
			do
			{
				PLTSQL_expr *expr;

				expr = read_sql_expression2(',', ';', ", or ;", &term);
				new->params = lappend(new->params, expr);
			} while (term == ',');
		}
	}

	return (PLTSQL_stmt *) new;
}


/* convenience routine to fetch the name of a T_DATUM */
static char *
NameOfDatum(PLwdatum *wdatum)
{
	if (wdatum->ident)
		return wdatum->ident;
	Assert(wdatum->idents != NIL);
	return NameListToString(wdatum->idents);
}

static void
check_assignable(PLTSQL_datum *datum, int location)
{
	switch (datum->dtype)
	{
		case PLTSQL_DTYPE_VAR:
			if (((PLTSQL_var *) datum)->isconst)
				ereport(ERROR,
						(errcode(ERRCODE_ERROR_IN_ASSIGNMENT),
						 errmsg("\"%s\" is declared CONSTANT",
								((PLTSQL_var *) datum)->refname),
						 parser_errposition(location)));
			break;
		case PLTSQL_DTYPE_ROW:
			/* always assignable? */
			break;
		case PLTSQL_DTYPE_REC:
			/* always assignable?  What about NEW/OLD? */
			break;
		case PLTSQL_DTYPE_RECFIELD:
			/* always assignable? */
			break;
		case PLTSQL_DTYPE_ARRAYELEM:
			/* always assignable? */
			break;
		default:
			elog(ERROR, "unrecognized dtype: %d", datum->dtype);
			break;
	}
}

/*
 * Read the argument of an INTO clause.  On entry, we have just read the
 * INTO keyword.
 */
static void
read_into_target(PLTSQL_rec **rec, PLTSQL_row **row, bool *strict)
{
	int			tok;

	/* Set default results */
	*rec = NULL;
	*row = NULL;
	if (strict)
		*strict = false;

	tok = yylex();
	if (strict && tok == K_STRICT)
	{
		*strict = true;
		tok = yylex();
	}

	/*
	 * Currently, a row or record variable can be the single INTO target,
	 * but not a member of a multi-target list.  So we throw error if there
	 * is a comma after it, because that probably means the user tried to
	 * write a multi-target list.  If this ever gets generalized, we should
	 * probably refactor read_into_scalar_list so it handles all cases.
	 */
	switch (tok)
	{
		case T_DATUM:
			if (yylval.wdatum.datum->dtype == PLTSQL_DTYPE_ROW)
			{
				check_assignable(yylval.wdatum.datum, yylloc);
				*row = (PLTSQL_row *) yylval.wdatum.datum;

				if ((tok = yylex()) == ',')
					ereport(ERROR,
							(errcode(ERRCODE_SYNTAX_ERROR),
							 errmsg("record or row variable cannot be part of multiple-item INTO list"),
							 parser_errposition(yylloc)));
				pltsql_push_back_token(tok);
			}
			else if (yylval.wdatum.datum->dtype == PLTSQL_DTYPE_REC)
			{
				check_assignable(yylval.wdatum.datum, yylloc);
				*rec = (PLTSQL_rec *) yylval.wdatum.datum;

				if ((tok = yylex()) == ',')
					ereport(ERROR,
							(errcode(ERRCODE_SYNTAX_ERROR),
							 errmsg("record or row variable cannot be part of multiple-item INTO list"),
							 parser_errposition(yylloc)));
				pltsql_push_back_token(tok);
			}
			else
			{
				*row = read_into_scalar_list(NameOfDatum(&(yylval.wdatum)),
											 yylval.wdatum.datum, yylloc);
			}
			break;

		default:
			/* just to give a better message than "syntax error" */
			current_token_is_not_variable(tok);
	}
}

/*
 * Given the first datum and name in the INTO list, continue to read
 * comma-separated scalar variables until we run out. Then construct
 * and return a fake "row" variable that represents the list of
 * scalars.
 */
static PLTSQL_row *
read_into_scalar_list(char *initial_name,
					  PLTSQL_datum *initial_datum,
					  int initial_location)
{
	int				 nfields;
	char			*fieldnames[1024];
	int				 varnos[1024];
	PLTSQL_row		*row;
	int				 tok;

	check_assignable(initial_datum, initial_location);
	fieldnames[0] = initial_name;
	varnos[0]	  = initial_datum->dno;
	nfields		  = 1;

	while ((tok = yylex()) == ',')
	{
		/* Check for array overflow */
		if (nfields >= 1024)
			ereport(ERROR,
					(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
					 errmsg("too many INTO variables specified"),
					 parser_errposition(yylloc)));

		tok = yylex();
		switch (tok)
		{
			case T_DATUM:
				check_assignable(yylval.wdatum.datum, yylloc);
				if (yylval.wdatum.datum->dtype == PLTSQL_DTYPE_ROW ||
					yylval.wdatum.datum->dtype == PLTSQL_DTYPE_REC)
					ereport(ERROR,
							(errcode(ERRCODE_SYNTAX_ERROR),
							 errmsg("\"%s\" is not a scalar variable",
									NameOfDatum(&(yylval.wdatum))),
							 parser_errposition(yylloc)));
				fieldnames[nfields] = NameOfDatum(&(yylval.wdatum));
				varnos[nfields++]	= yylval.wdatum.datum->dno;
				break;

			default:
				/* just to give a better message than "syntax error" */
				current_token_is_not_variable(tok);
		}
	}

	/*
	 * We read an extra, non-comma token from yylex(), so push it
	 * back onto the input stream
	 */
	pltsql_push_back_token(tok);

	row = palloc(sizeof(PLTSQL_row));
	row->dtype = PLTSQL_DTYPE_ROW;
	row->refname = pstrdup("*internal*");
	row->lineno = pltsql_location_to_lineno(initial_location);
	row->rowtupdesc = NULL;
	row->nfields = nfields;
	row->fieldnames = palloc(sizeof(char *) * nfields);
	row->varnos = palloc(sizeof(int) * nfields);
	while (--nfields >= 0)
	{
		row->fieldnames[nfields] = fieldnames[nfields];
		row->varnos[nfields] = varnos[nfields];
	}

	pltsql_adddatum((PLTSQL_datum *)row);

	return row;
}

/*
 * Convert a single scalar into a "row" list.  This is exactly
 * like read_into_scalar_list except we never consume any input.
 *
 * Note: lineno could be computed from location, but since callers
 * have it at hand already, we may as well pass it in.
 */
static PLTSQL_row *
make_scalar_list1(char *initial_name,
				  PLTSQL_datum *initial_datum,
				  int lineno, int location)
{
	PLTSQL_row		*row;

	check_assignable(initial_datum, location);

	row = palloc(sizeof(PLTSQL_row));
	row->dtype = PLTSQL_DTYPE_ROW;
	row->refname = pstrdup("*internal*");
	row->lineno = lineno;
	row->rowtupdesc = NULL;
	row->nfields = 1;
	row->fieldnames = palloc(sizeof(char *));
	row->varnos = palloc(sizeof(int));
	row->fieldnames[0] = initial_name;
	row->varnos[0] = initial_datum->dno;

	pltsql_adddatum((PLTSQL_datum *)row);

	return row;
}

/*
 * When the PL/TSQL parser expects to see a SQL statement, it is very
 * liberal in what it accepts; for example, we often assume an
 * unrecognized keyword is the beginning of a SQL statement. This
 * avoids the need to duplicate parts of the SQL grammar in the
 * PL/TSQL grammar, but it means we can accept wildly malformed
 * input. To try and catch some of the more obviously invalid input,
 * we run the strings we expect to be SQL statements through the main
 * SQL parser.
 *
 * We only invoke the raw parser (not the analyzer); this doesn't do
 * any database access and does not check any semantic rules, it just
 * checks for basic syntactic correctness. We do this here, rather
 * than after parsing has finished, because a malformed SQL statement
 * may cause the PL/TSQL parser to become confused about statement
 * borders. So it is best to bail out as early as we can.
 *
 * It is assumed that "stmt" represents a copy of the function source text
 * beginning at offset "location", with leader text of length "leaderlen"
 * (typically "SELECT ") prefixed to the source text.  We use this assumption
 * to transpose any error cursor position back to the function source text.
 * If no error cursor is provided, we'll just point at "location".
 */
static void
check_sql_expr(const char *stmt, int location, int leaderlen)
{
	sql_error_callback_arg cbarg;
	ErrorContextCallback  syntax_errcontext;
	MemoryContext oldCxt;

	if (!pltsql_check_syntax)
		return;

	cbarg.location = location;
	cbarg.leaderlen = leaderlen;

	syntax_errcontext.callback = pltsql_sql_error_callback;
	syntax_errcontext.arg = &cbarg;
	syntax_errcontext.previous = error_context_stack;
	error_context_stack = &syntax_errcontext;

	oldCxt = MemoryContextSwitchTo(compile_tmp_cxt);
	(void) raw_parser(stmt);
	MemoryContextSwitchTo(oldCxt);

	/* Restore former ereport callback */
	error_context_stack = syntax_errcontext.previous;
}

static void
pltsql_sql_error_callback(void *arg)
{
	sql_error_callback_arg *cbarg = (sql_error_callback_arg *) arg;
	int			errpos;

	/*
	 * First, set up internalerrposition to point to the start of the
	 * statement text within the function text.  Note this converts
	 * location (a byte offset) to a character number.
	 */
	parser_errposition(cbarg->location);

	/*
	 * If the core parser provided an error position, transpose it.
	 * Note we are dealing with 1-based character numbers at this point.
	 */
	errpos = geterrposition();
	if (errpos > cbarg->leaderlen)
	{
		int		myerrpos = getinternalerrposition();

		if (myerrpos > 0)		/* safety check */
			internalerrposition(myerrpos + errpos - cbarg->leaderlen - 1);
	}

	/* In any case, flush errposition --- we want internalerrpos only */
	errposition(0);
}

/*
 * Parse a SQL datatype name and produce a PLTSQL_type structure.
 *
 * The heavy lifting is done elsewhere.  Here we are only concerned
 * with setting up an errcontext link that will let us give an error
 * cursor pointing into the pltsql function source, if necessary.
 * This is handled the same as in check_sql_expr(), and we likewise
 * expect that the given string is a copy from the source text.
 */
static PLTSQL_type *
parse_datatype(const char *string, int location)
{
	Oid			type_id;
	int32		typmod;
	sql_error_callback_arg cbarg;
	ErrorContextCallback  syntax_errcontext;

	cbarg.location = location;
	cbarg.leaderlen = 0;

	syntax_errcontext.callback = pltsql_sql_error_callback;
	syntax_errcontext.arg = &cbarg;
	syntax_errcontext.previous = error_context_stack;
	error_context_stack = &syntax_errcontext;

	/* Let the main parser try to parse it under standard SQL rules */
	parseTypeString(string, &type_id, &typmod);

	/* Restore former ereport callback */
	error_context_stack = syntax_errcontext.previous;

	/* Okay, build a PLTSQL_type data structure for it */
	return pltsql_build_datatype(type_id, typmod,
								  pltsql_curr_compile->fn_input_collation);
}

/*
 * Check block starting and ending labels match.
 */
static void
check_labels(const char *start_label, const char *end_label, int end_location)
{
	if (end_label)
	{
		if (!start_label)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("end label \"%s\" specified for unlabelled block",
							end_label),
					 parser_errposition(end_location)));

		if (strcmp(start_label, end_label) != 0)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("end label \"%s\" differs from block's label \"%s\"",
							end_label, start_label),
					 parser_errposition(end_location)));
	}
}

/*
 * Read the arguments (if any) for a cursor, followed by the until token
 *
 * If cursor has no args, just swallow the until token and return NULL.
 * If it does have args, we expect to see "( arg [, arg ...] )" followed
 * by the until token, where arg may be a plain expression, or a named
 * parameter assignment of the form argname := expr. Consume all that and
 * return a SELECT query that evaluates the expression(s) (without the outer
 * parens).
 */
static PLTSQL_expr *
read_cursor_args(PLTSQL_var *cursor, int until, const char *expected)
{
	PLTSQL_expr *expr;
	PLTSQL_row *row;
	int			tok;
	int			argc;
	char	  **argv;
	StringInfoData ds;
	char	   *sqlstart = "SELECT ";
	bool		any_named = false;

	tok = yylex();
	if (cursor->cursor_explicit_argrow < 0)
	{
		/* No arguments expected */
		if (tok == '(')
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("cursor \"%s\" has no arguments",
							cursor->refname),
					 parser_errposition(yylloc)));

		if (tok != until)
			yyerror("syntax error");

		return NULL;
	}

	/* Else better provide arguments */
	if (tok != '(')
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("cursor \"%s\" has arguments",
						cursor->refname),
				 parser_errposition(yylloc)));

	/*
	 * Read the arguments, one by one.
	 */
	row = (PLTSQL_row *) pltsql_Datums[cursor->cursor_explicit_argrow];
	argv = (char **) palloc0(row->nfields * sizeof(char *));

	for (argc = 0; argc < row->nfields; argc++)
	{
		PLTSQL_expr *item;
		int		endtoken;
		int		argpos;
		int		tok1,
				tok2;
		int		arglocation;

		/* Check if it's a named parameter: "param := value" */
		pltsql_peek2(&tok1, &tok2, &arglocation, NULL);
		if (tok1 == IDENT && tok2 == COLON_EQUALS)
		{
			char   *argname;
			IdentifierLookup save_IdentifierLookup;

			/* Read the argument name, ignoring any matching variable */
			save_IdentifierLookup = pltsql_IdentifierLookup;
			pltsql_IdentifierLookup = IDENTIFIER_LOOKUP_DECLARE;
			yylex();
			argname = yylval.str;
			pltsql_IdentifierLookup = save_IdentifierLookup;

			/* Match argument name to cursor arguments */
			for (argpos = 0; argpos < row->nfields; argpos++)
			{
				if (strcmp(row->fieldnames[argpos], argname) == 0)
					break;
			}
			if (argpos == row->nfields)
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("cursor \"%s\" has no argument named \"%s\"",
								cursor->refname, argname),
						 parser_errposition(yylloc)));

			/*
			 * Eat the ":=". We already peeked, so the error should never
			 * happen.
			 */
			tok2 = yylex();
			if (tok2 != COLON_EQUALS)
				yyerror("syntax error");

			any_named = true;
		}
		else
			argpos = argc;

		if (argv[argpos] != NULL)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("duplicate value for cursor \"%s\" parameter \"%s\"",
							cursor->refname, row->fieldnames[argpos]),
					 parser_errposition(arglocation)));

		/*
		 * Read the value expression. To provide the user with meaningful
		 * parse error positions, we check the syntax immediately, instead of
		 * checking the final expression that may have the arguments
		 * reordered. Trailing whitespace must not be trimmed, because
		 * otherwise input of the form (param -- comment\n, param) would be
		 * translated into a form where the second parameter is commented
		 * out.
		 */
		item = read_sql_construct(',', ')', 0,
								  ",\" or \")",
								  sqlstart,
								  true, true,
								  false, /* do not trim */
								  NULL, &endtoken);

		argv[argpos] = item->query + strlen(sqlstart);

		if (endtoken == ')' && !(argc == row->nfields - 1))
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("not enough arguments for cursor \"%s\"",
							cursor->refname),
					 parser_errposition(yylloc)));

		if (endtoken == ',' && (argc == row->nfields - 1))
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("too many arguments for cursor \"%s\"",
							cursor->refname),
					 parser_errposition(yylloc)));
	}

	/* Make positional argument list */
	initStringInfo(&ds);
	appendStringInfoString(&ds, sqlstart);
	for (argc = 0; argc < row->nfields; argc++)
	{
		Assert(argv[argc] != NULL);

		/*
		 * Because named notation allows permutated argument lists, include
		 * the parameter name for meaningful runtime errors.
		 */
		appendStringInfoString(&ds, argv[argc]);
		if (any_named)
			appendStringInfo(&ds, " AS %s",
							 quote_identifier(row->fieldnames[argc]));
		if (argc < row->nfields - 1)
			appendStringInfoString(&ds, ", ");
	}
	appendStringInfoChar(&ds, ';');

	expr = palloc0(sizeof(PLTSQL_expr));
	expr->dtype			= PLTSQL_DTYPE_EXPR;
	expr->query			= pstrdup(ds.data);
	expr->plan			= NULL;
	expr->paramnos		= NULL;
	expr->ns            = pltsql_ns_top();
	pfree(ds.data);

	/* Next we'd better find the until token */
	tok = yylex();
	if (tok != until)
		yyerror("syntax error");

	return expr;
}

/*
 * Parse RAISE ... USING options
 */
static List *
read_raise_options(void)
{
	List	   *result = NIL;

	for (;;)
	{
		PLTSQL_raise_option *opt;
		int		tok;

		if ((tok = yylex()) == 0)
			yyerror("unexpected end of function definition");

		opt = (PLTSQL_raise_option *) palloc(sizeof(PLTSQL_raise_option));

		if (tok_is_keyword(tok, &yylval,
						   K_ERRCODE, "errcode"))
			opt->opt_type = PLTSQL_RAISEOPTION_ERRCODE;
		else if (tok_is_keyword(tok, &yylval,
								K_MESSAGE, "message"))
			opt->opt_type = PLTSQL_RAISEOPTION_MESSAGE;
		else if (tok_is_keyword(tok, &yylval,
								K_DETAIL, "detail"))
			opt->opt_type = PLTSQL_RAISEOPTION_DETAIL;
		else if (tok_is_keyword(tok, &yylval,
								K_HINT, "hint"))
			opt->opt_type = PLTSQL_RAISEOPTION_HINT;
		else
			yyerror("unrecognized RAISE statement option");

		tok = yylex();
		if (tok != '=' && tok != COLON_EQUALS)
			yyerror("syntax error, expected \"=\"");

		opt->expr = read_sql_expression2(',', ';', ", or ;", &tok);

		result = lappend(result, opt);

		if (tok == ';')
			break;
	}

	return result;
}

