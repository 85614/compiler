/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "grammar.y"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "include.h"
class AbstractASTNode;
extern char *yytext;
extern int yylex();
extern int column;
extern FILE * yyin;
extern int yylineno;
extern FileNode thisFile;
//StructTable *structTable;
void yyerror(const char *str);

#line 87 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ASSIGNOP = 258,
    OR = 259,
    AND = 260,
    SINGALAND = 261,
    RELOP = 262,
    MINUS = 263,
    PLUS = 264,
    STAR = 265,
    DIV = 266,
    MOD = 267,
    POWER = 268,
    NOT = 269,
    LP = 270,
    RP = 271,
    LB = 272,
    RB = 273,
    LOWER_THAN_ELSE = 274,
    SEMI = 275,
    COMMA = 276,
    RETURN = 277,
    IF = 278,
    ELSE = 279,
    WHILE = 280,
    STRUCT = 281,
    GETMEMBER = 282,
    ERRID = 283,
    INT1 = 284,
    TYPE1 = 285,
    ID1 = 286,
    FOR = 287,
    LC = 288,
    RC = 289
  };
#endif
/* Tokens.  */
#define ASSIGNOP 258
#define OR 259
#define AND 260
#define SINGALAND 261
#define RELOP 262
#define MINUS 263
#define PLUS 264
#define STAR 265
#define DIV 266
#define MOD 267
#define POWER 268
#define NOT 269
#define LP 270
#define RP 271
#define LB 272
#define RB 273
#define LOWER_THAN_ELSE 274
#define SEMI 275
#define COMMA 276
#define RETURN 277
#define IF 278
#define ELSE 279
#define WHILE 280
#define STRUCT 281
#define GETMEMBER 282
#define ERRID 283
#define INT1 284
#define TYPE1 285
#define ID1 286
#define FOR 287
#define LC 288
#define RC 289

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "grammar.y"

  struct TypeNode *type;
  struct IDNode *id;
  struct ExprNode *expr;
  struct StmtNode *stmt;
  struct ASTNode *temp;
  const char *str;

#line 213 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);





#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   579

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  175

#define YYUNDEFTOK  2
#define YYMAXUTOK   289


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    70,    70,    76,    80,    92,   101,   103,   107,   111,
     115,   121,   125,   131,   136,   141,   147,   151,   157,   163,
     169,   176,   184,   190,   197,   202,   208,   213,   220,   224,
     230,   238,   244,   248,   255,   260,   265,   270,   274,   278,
     282,   286,   290,   294,   298,   302,   306,   310,   314,   318,
     322,   326,   333,   336,   341,   344,   352,   356,   366,   370,
     382,   385,   388,   391,   394,   397,   400,   403,   406,   409,
     412,   415,   418,   421,   424,   427,   430,   433,   436,   440,
     443,   446,   449,   454,   458
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ASSIGNOP", "OR", "AND", "SINGALAND",
  "RELOP", "MINUS", "PLUS", "STAR", "DIV", "MOD", "POWER", "NOT", "LP",
  "RP", "LB", "RB", "LOWER_THAN_ELSE", "SEMI", "COMMA", "RETURN", "IF",
  "ELSE", "WHILE", "STRUCT", "GETMEMBER", "ERRID", "INT1", "TYPE1", "ID1",
  "FOR", "LC", "RC", "$accept", "Program", "ExtDefList", "ExtDef",
  "ExtDecList", "ID", "INT", "TYPE", "Specifier", "StructSpecifier",
  "StructDecList", "StructDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "DecFor", "Stmt", "Def", "DecList", "Dec", "VarDec", "Exp",
  "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289
};
# endif

#define YYPACT_NINF (-81)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-54)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      29,    -9,    -3,   -81,    37,    13,   -81,    34,    25,    26,
     -81,   -81,    39,   -81,   -81,   -81,   -81,    60,    32,     0,
     -81,   -81,    30,   -81,    -3,   -12,    41,    44,   -81,   -81,
     -81,    -3,    27,   -81,    58,   -81,   -81,    -3,   -13,   -81,
     -81,    65,   -81,   143,    64,   -81,   -81,   -81,   -81,    30,
     -81,   -11,    -3,   302,    -3,   302,   302,   123,    74,    75,
      -3,    82,   -81,    21,   -81,    -3,   -81,   -81,    78,   331,
     -81,   -81,   -81,    79,   -81,    84,   104,   -81,    96,   435,
     -81,   349,   302,   302,    -3,    11,   210,   302,    -3,   -81,
      80,   116,   -81,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   -81,   -81,   -81,   450,   465,   102,
      51,   213,   103,   -81,   540,   -81,   540,    -6,   403,   -81,
      -3,   302,   540,   551,   562,   315,   104,   104,    56,    56,
      56,    56,   419,   177,   177,   -81,   -81,   237,   367,   249,
     -81,   302,   -81,   -81,   540,   -81,   101,   -81,   177,   480,
     269,   280,   385,   540,   177,   -81,   177,   177,   495,   177,
     510,   291,   -81,   -81,   -81,   177,   -81,   177,   177,   525,
     -81,   -81,   -81,   177,   -81
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,    15,     0,     0,     3,    16,     0,     0,
      10,    13,     0,     1,     4,    17,     6,     0,    58,     0,
      11,     9,     0,     5,     0,     0,     0,     0,     8,    31,
       7,     0,     0,    19,    58,    12,    23,    27,     0,    25,
      14,     0,    29,     0,     0,    18,    20,    26,    22,     0,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,    77,    80,     0,    37,    30,     0,     0,
      21,    24,    82,    51,    73,     0,    71,    81,    72,     0,
      39,     0,     0,     0,     0,     0,     0,     0,     0,    52,
      54,    56,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,    70,    38,     0,     0,     0,
       0,     0,     0,    32,    33,    75,    84,     0,     0,    79,
       0,     0,    60,    62,    61,    63,    65,    64,    66,    67,
      68,    69,     0,     0,     0,    36,    53,     0,     0,     0,
      74,     0,    78,    55,    57,    76,    40,    42,     0,     0,
       0,     0,     0,    83,     0,    43,     0,     0,     0,     0,
       0,     0,    41,    46,    45,     0,    44,     0,     0,     0,
      50,    49,    48,     0,    47
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -81,   -81,   -81,   121,   -81,    -2,   106,   -81,     2,   -81,
     -81,    95,   -81,   -81,    85,   109,   -81,   -81,   -80,    50,
      16,   -81,     8,     9,   -81
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    17,    63,    64,     7,    65,     9,
      32,    33,    19,    38,    39,    66,    43,   112,    67,    68,
      89,    90,    91,    69,   117
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      12,    27,     8,    48,    36,    72,    18,     8,    49,    73,
     140,    10,   110,    -2,     1,   141,    20,    52,     3,    53,
      28,    54,    34,    42,    31,    55,    56,    37,    11,    44,
       1,   111,    35,    29,    31,    47,    86,    13,    87,     2,
      40,     3,    11,     3,    15,    16,    21,    25,    88,    26,
      74,    37,    77,   146,   147,     2,    11,     3,    84,     3,
       3,    45,    76,    34,    78,    79,    81,    72,   155,   102,
      40,   136,    22,   103,   162,    26,   163,   164,    42,   166,
      23,    24,   109,    50,    70,   170,   119,   171,   172,    82,
      83,   107,   108,   174,   114,   116,   118,    85,    92,   -53,
      72,   120,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   103,    99,   100,   101,   102,    34,   121,
     138,   103,   135,   139,    75,   154,    14,    46,    30,    52,
     144,    53,    41,    54,    71,   113,   143,    55,    56,     0,
       0,     0,     0,    80,    51,     0,   149,     0,   152,    52,
     153,    53,    40,    54,    11,     0,     0,    55,    56,   158,
     160,     0,     0,     0,     0,    57,    58,     0,    59,    60,
     169,     0,    40,     3,    11,    61,    29,    62,    51,     0,
       0,     0,     0,    52,     0,    53,     0,    54,     0,     0,
       0,    55,    56,     0,     0,     0,     0,     0,     0,    57,
      58,     0,    59,    60,     0,     0,    40,     3,    11,    61,
      29,    75,     0,     0,    75,     0,    52,     0,    53,    52,
      54,    53,     0,    54,    55,    56,   115,    55,    56,     0,
       0,     0,     0,   137,     0,     0,     0,     0,    75,    40,
       0,    11,    40,    52,    11,    53,     0,    54,     0,     0,
      75,    55,    56,   148,     0,    52,     0,    53,     0,    54,
       0,     0,     0,    55,    56,     0,    40,     0,    11,   151,
      75,     0,     0,     0,     0,    52,     0,    53,    40,    54,
      11,    75,     0,    55,    56,   157,    52,     0,    53,     0,
      54,     0,    75,     0,    55,    56,   159,    52,    40,    53,
      11,    54,     0,    75,     0,    55,    56,   168,    52,    40,
      53,    11,    54,     0,     0,     0,    55,    56,     0,     0,
      40,     0,    11,    97,    98,    99,   100,   101,   102,     0,
       0,    40,   103,    11,    93,    94,    95,     0,    96,    97,
      98,    99,   100,   101,   102,     0,     0,     0,   103,     0,
       0,   104,    93,    94,    95,     0,    96,    97,    98,    99,
     100,   101,   102,     0,     0,     0,   103,     0,     0,   106,
      93,    94,    95,     0,    96,    97,    98,    99,   100,   101,
     102,     0,     0,     0,   103,     0,     0,   150,    93,    94,
      95,     0,    96,    97,    98,    99,   100,   101,   102,     0,
       0,     0,   103,     0,     0,   161,    93,    94,    95,     0,
      96,    97,    98,    99,   100,   101,   102,     0,     0,     0,
     103,   142,    93,    94,    95,     0,    96,    97,    98,    99,
     100,   101,   102,     0,     0,     0,   103,   145,    93,    94,
      95,     0,    96,    97,    98,    99,   100,   101,   102,     0,
       0,   105,   103,    93,    94,    95,     0,    96,    97,    98,
      99,   100,   101,   102,     0,     0,   133,   103,    93,    94,
      95,     0,    96,    97,    98,    99,   100,   101,   102,     0,
       0,   134,   103,    93,    94,    95,     0,    96,    97,    98,
      99,   100,   101,   102,     0,     0,   156,   103,    93,    94,
      95,     0,    96,    97,    98,    99,   100,   101,   102,     0,
       0,   165,   103,    93,    94,    95,     0,    96,    97,    98,
      99,   100,   101,   102,     0,     0,   167,   103,    93,    94,
      95,     0,    96,    97,    98,    99,   100,   101,   102,     0,
       0,   173,   103,    93,    94,    95,     0,    96,    97,    98,
      99,   100,   101,   102,     0,     0,    95,   103,    96,    97,
      98,    99,   100,   101,   102,     0,     0,     0,   103,    96,
      97,    98,    99,   100,   101,   102,     0,     0,     0,   103
};

static const yytype_int16 yycheck[] =
{
       2,     1,     0,    16,    16,    16,     8,     5,    21,    20,
      16,    20,     1,     0,     1,    21,     8,     6,    30,     8,
      20,    10,    24,    34,    22,    14,    15,    25,    31,    31,
       1,    20,    24,    33,    32,    37,    15,     0,    17,    26,
      29,    30,    31,    30,    10,    20,    20,    15,    27,    17,
      52,    49,    54,   133,   134,    26,    31,    30,    60,    30,
      30,    34,    53,    65,    55,    56,    57,    16,   148,    13,
      29,    20,    33,    17,   154,    17,   156,   157,    34,   159,
      20,    21,    84,    18,    20,   165,    88,   167,   168,    15,
      15,    82,    83,   173,    85,    86,    87,    15,    20,    20,
      16,    21,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,    17,    10,    11,    12,    13,   120,     3,
     111,    17,    20,    20,     1,    24,     5,    32,    19,     6,
     121,     8,    26,    10,    49,    85,   120,    14,    15,    -1,
      -1,    -1,    -1,    20,     1,    -1,   137,    -1,   139,     6,
     141,     8,    29,    10,    31,    -1,    -1,    14,    15,   150,
     151,    -1,    -1,    -1,    -1,    22,    23,    -1,    25,    26,
     161,    -1,    29,    30,    31,    32,    33,    34,     1,    -1,
      -1,    -1,    -1,     6,    -1,     8,    -1,    10,    -1,    -1,
      -1,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    25,    26,    -1,    -1,    29,    30,    31,    32,
      33,     1,    -1,    -1,     1,    -1,     6,    -1,     8,     6,
      10,     8,    -1,    10,    14,    15,    16,    14,    15,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,     1,    29,
      -1,    31,    29,     6,    31,     8,    -1,    10,    -1,    -1,
       1,    14,    15,    16,    -1,     6,    -1,     8,    -1,    10,
      -1,    -1,    -1,    14,    15,    -1,    29,    -1,    31,    20,
       1,    -1,    -1,    -1,    -1,     6,    -1,     8,    29,    10,
      31,     1,    -1,    14,    15,    16,     6,    -1,     8,    -1,
      10,    -1,     1,    -1,    14,    15,    16,     6,    29,     8,
      31,    10,    -1,     1,    -1,    14,    15,    16,     6,    29,
       8,    31,    10,    -1,    -1,    -1,    14,    15,    -1,    -1,
      29,    -1,    31,     8,     9,    10,    11,    12,    13,    -1,
      -1,    29,    17,    31,     3,     4,     5,    -1,     7,     8,
       9,    10,    11,    12,    13,    -1,    -1,    -1,    17,    -1,
      -1,    20,     3,     4,     5,    -1,     7,     8,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    17,    -1,    -1,    20,
       3,     4,     5,    -1,     7,     8,     9,    10,    11,    12,
      13,    -1,    -1,    -1,    17,    -1,    -1,    20,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    -1,
      -1,    -1,    17,    -1,    -1,    20,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      17,    18,     3,     4,     5,    -1,     7,     8,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    17,    18,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    -1,
      -1,    16,    17,     3,     4,     5,    -1,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,    16,    17,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    -1,
      -1,    16,    17,     3,     4,     5,    -1,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,    16,    17,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    -1,
      -1,    16,    17,     3,     4,     5,    -1,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,    16,    17,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    -1,
      -1,    16,    17,     3,     4,     5,    -1,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,     5,    17,     7,     8,
       9,    10,    11,    12,    13,    -1,    -1,    -1,    17,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    17
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    26,    30,    36,    37,    38,    42,    43,    44,
      20,    31,    40,     0,    38,    10,    20,    39,    40,    47,
      57,    20,    33,    20,    21,    15,    17,     1,    20,    33,
      50,    43,    45,    46,    40,    57,    16,    43,    48,    49,
      29,    41,    34,    51,    40,    34,    46,    40,    16,    21,
      18,     1,     6,     8,    10,    14,    15,    22,    23,    25,
      26,    32,    34,    40,    41,    43,    50,    53,    54,    58,
      20,    49,    16,    20,    40,     1,    58,    40,    58,    58,
      20,    58,    15,    15,    40,    15,    15,    17,    27,    55,
      56,    57,    20,     3,     4,     5,     7,     8,     9,    10,
      11,    12,    13,    17,    20,    16,    20,    58,    58,    40,
       1,    20,    52,    54,    58,    16,    58,    59,    58,    40,
      21,     3,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    16,    16,    20,    20,    20,    58,    20,
      16,    21,    18,    55,    58,    18,    53,    53,    16,    58,
      20,    20,    58,    58,    24,    53,    16,    16,    58,    16,
      58,    20,    53,    53,    53,    16,    53,    16,    16,    58,
      53,    53,    53,    16,    53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    38,    38,    38,    38,
      38,    39,    39,    40,    41,    42,    43,    43,    44,    45,
      45,    46,    47,    47,    48,    48,    49,    49,    50,    50,
      51,    51,    52,    52,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    54,    54,    55,    55,    56,    56,    57,    57,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    59,    59
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     3,     2,     3,     3,     2,
       2,     1,     3,     1,     1,     1,     1,     2,     5,     1,
       2,     3,     4,     3,     3,     1,     2,     1,     3,     2,
       2,     0,     1,     1,     2,     2,     4,     1,     3,     2,
       5,     7,     5,     6,     7,     7,     7,     9,     8,     8,
       8,     2,     2,     2,     1,     3,     1,     3,     1,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     4,     3,     4,     1,     4,     3,
       1,     2,     2,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

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

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
      yychar = yylex ();
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 70 "grammar.y"
                    {
        thisFile.root = (yyvsp[0].temp);
    }
#line 1695 "y.tab.c"
    break;

  case 3:
#line 76 "grammar.y"
           {
        (yyval.temp) = new TempNode();
        (yyval.temp)->addChild((yyvsp[0].stmt));
    }
#line 1704 "y.tab.c"
    break;

  case 4:
#line 80 "grammar.y"
                        {
        if ((yyvsp[-1].temp) == NULL) {
            (yyval.temp) = (yyvsp[0].stmt);
        } else {
            if ((yyvsp[0].stmt) != NULL) {
                (yyvsp[-1].temp)->addChild((yyvsp[0].stmt));
            }
            (yyval.temp) = (yyvsp[-1].temp);
        }
    }
#line 1719 "y.tab.c"
    break;

  case 5:
#line 92 "grammar.y"
                                  {
        // printf("get ExtDef\n");
        //int a, b, c;
        new VarDefStmt((yyvsp[-2].type), (yyvsp[-1].temp));
        (yyvsp[-1].temp)->print(1);
        //$$ = new TempNode();
        //$$->addChild($1);
        //$$->addChild($2);
    }
#line 1733 "y.tab.c"
    break;

  case 6:
#line 101 "grammar.y"
                     {
    }
#line 1740 "y.tab.c"
    break;

  case 7:
#line 103 "grammar.y"
                              {
        //函数定义
        (yyval.stmt) = new FuncDefStmt((yyvsp[-2].type),(yyvsp[-1].temp),(yyvsp[0].stmt));
    }
#line 1749 "y.tab.c"
    break;

  case 8:
#line 107 "grammar.y"
                            {
        //函数声明
        (yyval.stmt) = new FuncDecStmt((yyvsp[-2].type),(yyvsp[-1].temp));
    }
#line 1758 "y.tab.c"
    break;

  case 9:
#line 111 "grammar.y"
                           {
        //结构体定义
        (yyval.stmt) = (yyvsp[-1].stmt);
    }
#line 1767 "y.tab.c"
    break;

  case 10:
#line 115 "grammar.y"
                 {
        yyerrok;
        (yyval.stmt) = NULL;
    }
#line 1776 "y.tab.c"
    break;

  case 11:
#line 121 "grammar.y"
                   {
        (yyval.temp) = new TempNode();
        (yyval.temp)->addChild((yyvsp[0].temp));
    }
#line 1785 "y.tab.c"
    break;

  case 12:
#line 125 "grammar.y"
                              {
        (yyvsp[-2].temp)->addChild((yyvsp[0].temp));
        (yyval.temp) = (yyvsp[-2].temp);
    }
#line 1794 "y.tab.c"
    break;

  case 13:
#line 131 "grammar.y"
        {
        (yyval.id) = new IDNode((yyvsp[0].str));
    }
#line 1802 "y.tab.c"
    break;

  case 14:
#line 136 "grammar.y"
          {
        (yyval.expr) = new ConstExprNode((yyvsp[0].str));
    }
#line 1810 "y.tab.c"
    break;

  case 15:
#line 141 "grammar.y"
            {
        (yyval.type) = TypeNode::getType((yyvsp[0].str));
    }
#line 1818 "y.tab.c"
    break;

  case 16:
#line 147 "grammar.y"
                {
        //类型本身：int
        (yyval.type) = (yyvsp[0].type);
    }
#line 1827 "y.tab.c"
    break;

  case 17:
#line 151 "grammar.y"
                {
        //指针：int *
        (yyval.type) = new PointerTypeNode((yyvsp[-1].type));
    }
#line 1836 "y.tab.c"
    break;

  case 18:
#line 157 "grammar.y"
                                               {
        //结构体类型定义：struct structname （ 结构体定义列表 ）
        (yyval.stmt) = new StructDefStmt((yyvsp[-3].id), (yyvsp[-1].temp));
    }
#line 1845 "y.tab.c"
    break;

  case 19:
#line 163 "grammar.y"
                         {
        //结构体声明列表中只有一个声明
        (yyval.temp) = new TempNode();
        (yyval.temp)->addChild((yyvsp[0].stmt));
        //$$ = $1;
    }
#line 1856 "y.tab.c"
    break;

  case 20:
#line 169 "grammar.y"
                              {
        //递归声明结构
        (yyvsp[-1].temp)->addChild((yyvsp[0].stmt));
        (yyval.temp) = (yyvsp[-1].temp);
    }
#line 1866 "y.tab.c"
    break;

  case 21:
#line 176 "grammar.y"
                             {
        //：结构体类型 id ；
        (yyval.stmt) = new VarDefStmt((yyvsp[-2].type), (yyvsp[-1].id));
    }
#line 1875 "y.tab.c"
    break;

  case 22:
#line 184 "grammar.y"
                         {
        //：函数名 （ 参数列表 ）
        (yyval.temp) = new TempNode();
        (yyval.temp)->addChild((yyvsp[-3].id));
        (yyval.temp)->addChild((yyvsp[-1].temp));
    }
#line 1886 "y.tab.c"
    break;

  case 23:
#line 190 "grammar.y"
               {
        //：函数名 （ ）
        (yyval.temp) = new TempNode();
        (yyval.temp)->addChild((yyvsp[-2].id));
    }
#line 1896 "y.tab.c"
    break;

  case 24:
#line 197 "grammar.y"
                                {
        //递归参数列表：参数列表 ， 参数声明
        (yyvsp[-2].temp) -> addChild((yyvsp[0].temp));
        (yyval.temp) = (yyvsp[-2].temp);
    }
#line 1906 "y.tab.c"
    break;

  case 25:
#line 202 "grammar.y"
               {
        //参数声明比如：int 变量名
        (yyval.temp) = (yyvsp[0].temp);
    }
#line 1915 "y.tab.c"
    break;

  case 26:
#line 208 "grammar.y"
                       {
        (yyval.temp) = new TempNode();
        (yyval.temp) -> addChild((yyvsp[-1].type));
        (yyval.temp) -> addChild((yyvsp[0].id));
    }
#line 1925 "y.tab.c"
    break;

  case 27:
#line 213 "grammar.y"
                {
        //无具体意义void fun(int)
    }
#line 1933 "y.tab.c"
    break;

  case 28:
#line 220 "grammar.y"
                   {
        //：{ 语句块 }
        (yyval.stmt) = new BlockStmt((yyvsp[-1].temp));
    }
#line 1942 "y.tab.c"
    break;

  case 29:
#line 224 "grammar.y"
               {
        yyerrok;
    }
#line 1950 "y.tab.c"
    break;

  case 30:
#line 230 "grammar.y"
                      {
        //递归语句列表
        //只有一个语句
        if ((yyvsp[-1].temp) == NULL) 
            (yyvsp[-1].temp) = new TempNode();
        (yyvsp[-1].temp) -> addChild((yyvsp[0].stmt));
        (yyval.temp) = (yyvsp[-1].temp);
    }
#line 1963 "y.tab.c"
    break;

  case 31:
#line 238 "grammar.y"
      {
        (yyval.temp) = NULL;
    }
#line 1971 "y.tab.c"
    break;

  case 32:
#line 244 "grammar.y"
        {
        //
        (yyval.stmt) = (yyvsp[0].stmt);
    }
#line 1980 "y.tab.c"
    break;

  case 33:
#line 248 "grammar.y"
          {
        //
        (yyval.stmt) = new ExprStmtNode((yyvsp[0].expr));
    }
#line 1989 "y.tab.c"
    break;

  case 34:
#line 255 "grammar.y"
               {
        //表达式 ；
            (yyval.stmt) = new ExprStmtNode((yyvsp[-1].expr));
        
    }
#line 1999 "y.tab.c"
    break;

  case 35:
#line 260 "grammar.y"
               {
        //定义语句 ；
            (yyval.stmt) = (yyvsp[-1].stmt);
        
    }
#line 2009 "y.tab.c"
    break;

  case 36:
#line 265 "grammar.y"
                        {
        //声明结构体变量：struct structname a ；
        StructTypeNode *t = StructTypeNode::getStructType((yyvsp[-2].id));
        (yyval.stmt) = new VarDefStmt(t, (yyvsp[-1].id));
    }
#line 2019 "y.tab.c"
    break;

  case 37:
#line 270 "grammar.y"
             {
        //语句块
        (yyval.stmt) = (yyvsp[0].stmt);
    }
#line 2028 "y.tab.c"
    break;

  case 38:
#line 274 "grammar.y"
                      {
        //return语句：return 表达式 ；
        (yyval.stmt) = new ReturnStmt((yyvsp[-1].expr));
    }
#line 2037 "y.tab.c"
    break;

  case 39:
#line 278 "grammar.y"
                  {
        //return语句：return ；
        (yyval.stmt) = new ReturnStmt(NULL);
    }
#line 2046 "y.tab.c"
    break;

  case 40:
#line 282 "grammar.y"
                        {
        //条件语句：if （ 表达式 ）语句
        (yyval.stmt) = new IFStmt((yyvsp[-2].expr), (yyvsp[0].stmt), nullptr);
    }
#line 2055 "y.tab.c"
    break;

  case 41:
#line 286 "grammar.y"
                                                        {
        //条件语句：if （ 表达式 ） 语句 else 语句
        (yyval.stmt) = new IFStmt((yyvsp[-4].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt));
    }
#line 2064 "y.tab.c"
    break;

  case 42:
#line 290 "grammar.y"
                           {
        //while语句：while （ 表达式 ）语句
        (yyval.stmt) = new WhileStmt((yyvsp[-2].expr), (yyvsp[0].stmt));
    }
#line 2073 "y.tab.c"
    break;

  case 43:
#line 294 "grammar.y"
                               {
        //无限循环的for语句：for （ ； ；）语句
        (yyval.stmt) = new ForStmt(NULL, NULL, NULL, (yyvsp[0].stmt));
    }
#line 2082 "y.tab.c"
    break;

  case 44:
#line 298 "grammar.y"
                                      {
        //：for（ 声明 ； ；） 语句
        (yyval.stmt) = new ForStmt((yyvsp[-4].stmt), NULL, NULL, (yyvsp[0].stmt));
    }
#line 2091 "y.tab.c"
    break;

  case 45:
#line 302 "grammar.y"
                                   {
        //：for （ ； 表达式 ；） 语句 
        (yyval.stmt) = new ForStmt(NULL, (yyvsp[-3].expr), NULL, (yyvsp[0].stmt));
    }
#line 2100 "y.tab.c"
    break;

  case 46:
#line 306 "grammar.y"
                                   {
        //：for （ ； ； 表达式 ） 语句
        (yyval.stmt) = new ForStmt(NULL, NULL, (yyvsp[-2].expr), (yyvsp[0].stmt));
    }
#line 2109 "y.tab.c"
    break;

  case 47:
#line 310 "grammar.y"
                                              {
        //：for （ 声明 ； 表达式 ； 表达式 ） 语句
        (yyval.stmt) = new ForStmt((yyvsp[-6].stmt), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stmt));
    }
#line 2118 "y.tab.c"
    break;

  case 48:
#line 314 "grammar.y"
                                          {
        //：for （ 声明 ； 表达式 ； ） 语句
        (yyval.stmt) = new ForStmt((yyvsp[-5].stmt), (yyvsp[-3].expr), NULL, (yyvsp[0].stmt));
    }
#line 2127 "y.tab.c"
    break;

  case 49:
#line 318 "grammar.y"
                                          {
        //：for （ 声明 ； ； 表达式 ） 语句
        (yyval.stmt) = new ForStmt((yyvsp[-5].stmt), NULL, (yyvsp[-2].expr), (yyvsp[0].stmt));
    }
#line 2136 "y.tab.c"
    break;

  case 50:
#line 322 "grammar.y"
                                       {
        //：for （ ； 表达式 ； 表达式 ） 语句
        (yyval.stmt) = new ForStmt(NULL, (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stmt));
    }
#line 2145 "y.tab.c"
    break;

  case 51:
#line 326 "grammar.y"
                 {
        //错误
        yyerrok;
    }
#line 2154 "y.tab.c"
    break;

  case 52:
#line 333 "grammar.y"
                       {
        (yyval.stmt) = new VarDefStmt((yyvsp[-1].type), (yyvsp[0].temp));
    }
#line 2162 "y.tab.c"
    break;

  case 53:
#line 336 "grammar.y"
                 {
        yyerrok;
    }
#line 2170 "y.tab.c"
    break;

  case 54:
#line 341 "grammar.y"
             {
        (yyval.temp) = (yyvsp[0].temp);
    }
#line 2178 "y.tab.c"
    break;

  case 55:
#line 344 "grammar.y"
                        {
        //a , 声明列表
        (yyval.temp) = new TempNode();
        (yyval.temp) -> addChild((yyvsp[-2].temp));
        (yyval.temp) -> addChild((yyvsp[0].temp));
    }
#line 2189 "y.tab.c"
    break;

  case 56:
#line 352 "grammar.y"
            {
        (yyval.temp) = (yyvsp[0].temp);
        // printf("get Dec\n");
    }
#line 2198 "y.tab.c"
    break;

  case 57:
#line 356 "grammar.y"
                          {
        (yyval.temp) = new TempNode();
        (yyval.temp) -> addChild((yyvsp[-2].temp));
        (yyval.temp) -> addChild((yyvsp[0].expr));
        (yyval.temp) -> addMsg("=");
    }
#line 2209 "y.tab.c"
    break;

  case 58:
#line 366 "grammar.y"
           {
        //变量：varname
        (yyval.temp) = (yyvsp[0].id);
    }
#line 2218 "y.tab.c"
    break;

  case 59:
#line 370 "grammar.y"
                   {
        //变量数组：varname [ 数字 ]
        (yyval.temp) = new TempNode();
        (yyval.temp)->addChild((yyvsp[-3].id));
        (yyval.temp)->addChild((yyvsp[-1].expr));
        (yyval.temp)->addMsg("[]");
    }
#line 2230 "y.tab.c"
    break;

  case 60:
#line 382 "grammar.y"
                     {
        (yyval.expr) = new OP2ExprNode(op_e::Assignop, (yyvsp[-2].expr), (yyvsp[0].expr));
    }
#line 2238 "y.tab.c"
    break;

  case 61:
#line 385 "grammar.y"
                  {
        (yyval.expr) = new OP2ExprNode(op_e::And, (yyvsp[-2].expr), (yyvsp[0].expr));
    }
#line 2246 "y.tab.c"
    break;

  case 62:
#line 388 "grammar.y"
                 {
        (yyval.expr) = new OP2ExprNode(op_e::Or, (yyvsp[-2].expr), (yyvsp[0].expr));
    }
#line 2254 "y.tab.c"
    break;

  case 63:
#line 391 "grammar.y"
                    {
        (yyval.expr) = new OP2ExprNode(op_e::Relop, (yyvsp[-1].str), (yyvsp[-2].expr), (yyvsp[0].expr));
    }
#line 2262 "y.tab.c"
    break;

  case 64:
#line 394 "grammar.y"
                   {
        (yyval.expr) = new OP2ExprNode(op_e::Plus, (yyvsp[-2].expr), (yyvsp[0].expr));
    }
#line 2270 "y.tab.c"
    break;

  case 65:
#line 397 "grammar.y"
                    {
        (yyval.expr) = new OP2ExprNode(op_e::Minus, (yyvsp[-2].expr), (yyvsp[0].expr));
    }
#line 2278 "y.tab.c"
    break;

  case 66:
#line 400 "grammar.y"
                   {
        (yyval.expr) = new OP2ExprNode(op_e::Times, (yyvsp[-2].expr), (yyvsp[0].expr));
    }
#line 2286 "y.tab.c"
    break;

  case 67:
#line 403 "grammar.y"
                  {
        (yyval.expr) = new OP2ExprNode(op_e::Div, (yyvsp[-2].expr), (yyvsp[0].expr));
    }
#line 2294 "y.tab.c"
    break;

  case 68:
#line 406 "grammar.y"
                  {
        (yyval.expr) = new OP2ExprNode(op_e::Mod, (yyvsp[-2].expr), (yyvsp[0].expr));
    }
#line 2302 "y.tab.c"
    break;

  case 69:
#line 409 "grammar.y"
                    {
        (yyval.expr) = new OP2ExprNode(op_e::Power, (yyvsp[-2].expr), (yyvsp[0].expr));
    }
#line 2310 "y.tab.c"
    break;

  case 70:
#line 412 "grammar.y"
                {
        (yyval.expr) = (yyvsp[-1].expr);
    }
#line 2318 "y.tab.c"
    break;

  case 71:
#line 415 "grammar.y"
                {
        (yyval.expr) = new OP1ExprNode(op_e::Minus, (yyvsp[0].expr));
    }
#line 2326 "y.tab.c"
    break;

  case 72:
#line 418 "grammar.y"
              {
        (yyval.expr) = new OP1ExprNode(op_e::Not, (yyvsp[0].expr));
    }
#line 2334 "y.tab.c"
    break;

  case 73:
#line 421 "grammar.y"
                   {
        (yyval.expr) = new OP1ExprNode(op_e::SignalAnd, new VarExprNode((yyvsp[0].id)));
    }
#line 2342 "y.tab.c"
    break;

  case 74:
#line 424 "grammar.y"
                    {
        (yyval.expr) = new FunCallExprNode((yyvsp[-3].id), (yyvsp[-1].temp));
    }
#line 2350 "y.tab.c"
    break;

  case 75:
#line 427 "grammar.y"
               {
        (yyval.expr) = new FunCallExprNode((yyvsp[-2].id), nullptr);
    }
#line 2358 "y.tab.c"
    break;

  case 76:
#line 430 "grammar.y"
                    {
        (yyval.expr) = new OP2ExprNode(op_e::GetArrayValue, (yyvsp[-3].expr), (yyvsp[-1].expr));
    }
#line 2366 "y.tab.c"
    break;

  case 77:
#line 433 "grammar.y"
         {
        (yyval.expr) = new VarExprNode((yyvsp[0].id));
    }
#line 2374 "y.tab.c"
    break;

  case 78:
#line 436 "grammar.y"
                   {
        VarExprNode *t = new VarExprNode((yyvsp[-3].id));
        (yyval.expr) = new OP2ExprNode(op_e::GetArrayValue, t, (yyvsp[-1].expr));
    }
#line 2383 "y.tab.c"
    break;

  case 79:
#line 440 "grammar.y"
                      {
        (yyval.expr) = new OP2ExprNode(op_e::GetMember, new VarExprNode((yyvsp[-2].id)), new VarExprNode((yyvsp[0].id)));
    }
#line 2391 "y.tab.c"
    break;

  case 80:
#line 443 "grammar.y"
          {
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 2399 "y.tab.c"
    break;

  case 81:
#line 446 "grammar.y"
              {
        (yyval.expr) = new OP1ExprNode(op_e::GetValue, new VarExprNode((yyvsp[0].id)));
    }
#line 2407 "y.tab.c"
    break;

  case 82:
#line 449 "grammar.y"
               {
        yyerrok;
    }
#line 2415 "y.tab.c"
    break;

  case 83:
#line 454 "grammar.y"
                     {
        (yyvsp[-2].temp) -> addChild((yyvsp[0].expr));
        (yyval.temp) = (yyvsp[-2].temp);
    }
#line 2424 "y.tab.c"
    break;

  case 84:
#line 458 "grammar.y"
          {
        (yyval.temp) = new TempNode();
        (yyval.temp) -> addChild((yyvsp[0].expr));
    }
#line 2433 "y.tab.c"
    break;


#line 2437 "y.tab.c"

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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
#line 464 "grammar.y"


void yyerror(const char* s) {
	fprintf(stderr, "Parse error: At line %d. %s\n", yylineno, s);
	exit(1);
}

std::string replaceExtName(char* fileName) {
    int dotIndex = 0;
    int nameLength = strlen(fileName);
    for (int i = nameLength - 1; i >= 0; i--) {
        if (fileName[i] == '.') {
            dotIndex = i;
            break;
        }
    }
    char* buf = new char[dotIndex];
    strncpy(buf, fileName, dotIndex);
    std::string rev(buf);
    rev += ".asm";
    return rev;
}


void print_word_list();
void test_lexer()
{
    FILE* file = fopen("test.c", "r");
    yyin = file;
    do {
		yyparse();
	} while(!feof(yyin));
    print_word_list();
    thisFile.print(0);
}

/*
int main(int argc,char* argv[])
{
    InterMediate* im;
    bool flag_print_ast = false;
    bool flag_print_ir = false;
    bool flag_print_asm = false;
    char* filename = NULL;
    if (argc == 1) {
        printf("Error! Please input file name!\n");
        printf("Usage: parser [-t] [-i] [-a] [-d]\n");
        printf("  -t  print the abstract syntax tree (AST)\n");
        printf("  -i  print IR code\n");
        printf("  -a  print asm code\n");
        printf("  -d  debug mode print all\n");
        return -1;
    } else if (argc >= 2) {
        for (int i=1; i<argc; i++) {
            if (*argv[i] != '-') {
                if (filename == NULL) filename = argv[i];
            }
            else if (strcmp(argv[i], "-t") == 0) flag_print_ast = true;
            else if (strcmp(argv[i], "-i") == 0) flag_print_ir = true;
            else if (strcmp(argv[i], "-a") == 0) flag_print_asm = true;
            else if (strcmp(argv[i], "-d") == 0) {
                flag_print_ast = true;
                flag_print_ir = true;
                flag_print_asm = true;
            }
            else printf("Invalid parameter \"%s\"\n", argv[i]);
        }
    }
    FILE* file = fopen(filename, "r");
    yyin = file;
    do {
		yyparse();
	} while(!feof(yyin));
    if (flag_print_ast) {
        root->printTree();
    }
    im = new InterMediate((RootASTNode *)root, structTable);
    im->Generate(im->getRoot(), im->getTable());
    if (flag_print_ir) {
        im->printQuads();
    }
    AsmGenerator* asmgenerator = new AsmGenerator(im->getQuads(), im->getTempVars(), im->getTable(), im->getFuncTable());
    asmgenerator->generate();
    if (flag_print_asm) {
        std::cout << asmgenerator->getAsmCode();
    }

    std::string outFileName = replaceExtName(filename);
    std::ofstream outasm(outFileName);
    outasm << asmgenerator->getAsmCode();
    return 0;
}
*/
