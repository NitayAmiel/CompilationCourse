/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"


#include "nodes.hpp"
#include "output.hpp"
#include <iostream>

// bison declarations
extern int yylineno;
extern int yylex();

void yyerror(const char*);

// root of the AST, set by the parser and used by other parts of the compiler
std::shared_ptr<ast::Node> program;

using namespace std;

// TODO: Place any additional declarations here

#line 91 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SC = 3,                         /* SC  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_ADD = 6,                        /* ADD  */
  YYSYMBOL_MUL = 7,                        /* MUL  */
  YYSYMBOL_SUB = 8,                        /* SUB  */
  YYSYMBOL_DIV = 9,                        /* DIV  */
  YYSYMBOL_VOID = 10,                      /* VOID  */
  YYSYMBOL_BYTE = 11,                      /* BYTE  */
  YYSYMBOL_BOOL = 12,                      /* BOOL  */
  YYSYMBOL_AND = 13,                       /* AND  */
  YYSYMBOL_OR = 14,                        /* OR  */
  YYSYMBOL_TRUE = 15,                      /* TRUE  */
  YYSYMBOL_FALSE = 16,                     /* FALSE  */
  YYSYMBOL_RETURN = 17,                    /* RETURN  */
  YYSYMBOL_IF = 18,                        /* IF  */
  YYSYMBOL_ELSE = 19,                      /* ELSE  */
  YYSYMBOL_WHILE = 20,                     /* WHILE  */
  YYSYMBOL_BREAK = 21,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 22,                  /* CONTINUE  */
  YYSYMBOL_COMMA = 23,                     /* COMMA  */
  YYSYMBOL_LPAREN = 24,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 25,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 26,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 27,                    /* RBRACE  */
  YYSYMBOL_ASSIGN = 28,                    /* ASSIGN  */
  YYSYMBOL_NUM = 29,                       /* NUM  */
  YYSYMBOL_NUM_B = 30,                     /* NUM_B  */
  YYSYMBOL_STRING = 31,                    /* STRING  */
  YYSYMBOL_EQ = 32,                        /* EQ  */
  YYSYMBOL_NE = 33,                        /* NE  */
  YYSYMBOL_LT = 34,                        /* LT  */
  YYSYMBOL_GT = 35,                        /* GT  */
  YYSYMBOL_LE = 36,                        /* LE  */
  YYSYMBOL_GE = 37,                        /* GE  */
  YYSYMBOL_NOT = 38,                       /* NOT  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_Program = 40,                   /* Program  */
  YYSYMBOL_Funcs = 41,                     /* Funcs  */
  YYSYMBOL_FuncDecl = 42,                  /* FuncDecl  */
  YYSYMBOL_RetType = 43,                   /* RetType  */
  YYSYMBOL_Formals = 44,                   /* Formals  */
  YYSYMBOL_FormalsList = 45,               /* FormalsList  */
  YYSYMBOL_FormalDecl = 46,                /* FormalDecl  */
  YYSYMBOL_Statements = 47,                /* Statements  */
  YYSYMBOL_Statement = 48,                 /* Statement  */
  YYSYMBOL_Call = 49,                      /* Call  */
  YYSYMBOL_ExpList = 50,                   /* ExpList  */
  YYSYMBOL_Type = 51,                      /* Type  */
  YYSYMBOL_Exp = 52                        /* Exp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   326

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  106

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int8 yyrline[] =
{
       0,    38,    38,    41,    42,    45,    48,    49,    52,    53,
      56,    57,    60,    63,    64,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    81,    82,    85,
      86,    89,    90,    91,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SC", "INT", "ID",
  "ADD", "MUL", "SUB", "DIV", "VOID", "BYTE", "BOOL", "AND", "OR", "TRUE",
  "FALSE", "RETURN", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "COMMA",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "ASSIGN", "NUM", "NUM_B",
  "STRING", "EQ", "NE", "LT", "GT", "LE", "GE", "NOT", "$accept",
  "Program", "Funcs", "FuncDecl", "RetType", "Formals", "FormalsList",
  "FormalDecl", "Statements", "Statement", "Call", "ExpList", "Type",
  "Exp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-29)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     119,   -29,   -29,   -29,   -29,     6,   -29,   119,    16,   -29,
     -29,   -29,   -11,    26,     0,   -29,    11,    24,     9,    26,
     -29,   300,   -29,    -5,     2,    15,    17,    39,    58,   300,
     281,   -29,    60,    64,   134,   151,   -29,    51,   -29,   -29,
     122,   -29,   -29,   -29,   151,   -29,    59,   151,   151,   -29,
     -29,    47,   -29,   -29,   -29,     8,   -29,    63,   170,    73,
      65,   202,    50,   -29,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   215,   247,   -29,   -29,
     151,   -29,   151,   -29,   151,   -29,     5,   -29,     5,   -29,
      50,    50,    50,    50,    50,    50,    50,    50,   300,   300,
     108,   -29,    50,   -29,   -29,   -29
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,    31,     7,    32,    33,     0,     2,     4,     0,     6,
       1,     3,     0,     9,     0,     8,    10,     0,     0,     0,
      12,     0,    11,     0,     0,     0,     0,     0,     0,     0,
       0,    13,     0,     0,     0,     0,    20,    39,    44,    45,
       0,    41,    42,    43,     0,    40,     0,     0,     0,    25,
      26,     0,     5,    14,    19,     0,    28,     0,    29,     0,
       0,     0,    46,    21,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    15,    16,
       0,    27,     0,    18,     0,    34,    35,    37,    36,    38,
      47,    48,    49,    50,    51,    52,    53,    54,     0,     0,
       0,    30,    55,    22,    24,    17
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -29,   -29,    76,   -29,   -29,   -29,    66,   -29,   -29,   -28,
     -21,     7,     3,   -20
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,     8,    14,    15,    16,    30,    31,
      45,    57,    33,    58
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      32,    51,    53,     9,    46,    36,    10,    37,    32,    32,
       9,    79,    65,    13,    67,    59,    17,    38,    39,    34,
      61,    12,    17,    35,    62,    18,    40,    76,    77,    20,
       1,    41,    42,    43,    19,    21,    80,     3,     4,    47,
      44,    48,    49,    60,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    64,    65,    66,    67,
     100,    50,    63,    54,   102,    64,    65,    66,    67,    55,
     103,   104,    68,    69,    78,    34,    83,    32,    32,    64,
      65,    66,    67,    11,     0,    22,    68,    69,    81,   101,
      84,    70,    71,    72,    73,    74,    75,     0,     0,     0,
       0,     0,     0,     0,     0,    70,    71,    72,    73,    74,
      75,   105,     0,     0,    64,    65,    66,    67,     0,     0,
       0,    68,    69,     1,     0,     0,     1,    37,     0,     2,
       3,     4,     0,     3,     4,     0,     0,    38,    39,    37,
      70,    71,    72,    73,    74,    75,    40,     0,     0,    38,
      39,    41,    42,    43,     0,     0,    37,     0,    40,    56,
      44,     0,     0,    41,    42,    43,    38,    39,     0,     0,
       0,     0,    44,     0,     0,    40,    64,    65,    66,    67,
      41,    42,    43,    68,    69,     0,     0,     0,     0,    44,
       0,     0,     0,    82,     0,     0,     0,     0,     0,     0,
       0,     0,    70,    71,    72,    73,    74,    75,    64,    65,
      66,    67,     0,     0,     0,    68,    69,     0,     0,     0,
       0,    64,    65,    66,    67,     0,     0,    85,    68,    69,
       0,     0,     0,     0,    70,    71,    72,    73,    74,    75,
      98,     0,     0,     0,     0,     0,     0,    70,    71,    72,
      73,    74,    75,    64,    65,    66,    67,     0,     0,     0,
      68,    69,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    99,     0,     0,     0,     0,     0,     0,    70,
      71,    72,    73,    74,    75,     1,    23,     0,     0,     0,
       0,     0,     3,     4,     0,     0,     0,     0,    24,    25,
       0,    26,    27,    28,     1,    23,     0,    29,    52,     0,
       0,     3,     4,     0,     0,     0,     0,    24,    25,     0,
      26,    27,    28,     0,     0,     0,    29
};

static const yytype_int8 yycheck[] =
{
      21,    29,    30,     0,    24,     3,     0,     5,    29,    30,
       7,     3,     7,    24,     9,    35,    13,    15,    16,    24,
      40,     5,    19,    28,    44,    25,    24,    47,    48,     5,
       4,    29,    30,    31,    23,    26,    28,    11,    12,    24,
      38,    24,     3,    40,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,     6,     7,     8,     9,
      80,     3,     3,     3,    84,     6,     7,     8,     9,     5,
      98,    99,    13,    14,    27,    24,     3,    98,    99,     6,
       7,     8,     9,     7,    -1,    19,    13,    14,    25,    82,
      25,    32,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,
      37,     3,    -1,    -1,     6,     7,     8,     9,    -1,    -1,
      -1,    13,    14,     4,    -1,    -1,     4,     5,    -1,    10,
      11,    12,    -1,    11,    12,    -1,    -1,    15,    16,     5,
      32,    33,    34,    35,    36,    37,    24,    -1,    -1,    15,
      16,    29,    30,    31,    -1,    -1,     5,    -1,    24,    25,
      38,    -1,    -1,    29,    30,    31,    15,    16,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    24,     6,     7,     8,     9,
      29,    30,    31,    13,    14,    -1,    -1,    -1,    -1,    38,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    37,     6,     7,
       8,     9,    -1,    -1,    -1,    13,    14,    -1,    -1,    -1,
      -1,     6,     7,     8,     9,    -1,    -1,    25,    13,    14,
      -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,    37,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    37,     6,     7,     8,     9,    -1,    -1,    -1,
      13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    36,    37,     4,     5,    -1,    -1,    -1,
      -1,    -1,    11,    12,    -1,    -1,    -1,    -1,    17,    18,
      -1,    20,    21,    22,     4,     5,    -1,    26,    27,    -1,
      -1,    11,    12,    -1,    -1,    -1,    -1,    17,    18,    -1,
      20,    21,    22,    -1,    -1,    -1,    26
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,    10,    11,    12,    40,    41,    42,    43,    51,
       0,    41,     5,    24,    44,    45,    46,    51,    25,    23,
       5,    26,    45,     5,    17,    18,    20,    21,    22,    26,
      47,    48,    49,    51,    24,    28,     3,     5,    15,    16,
      24,    29,    30,    31,    38,    49,    52,    24,    24,     3,
       3,    48,    27,    48,     3,     5,    25,    50,    52,    52,
      51,    52,    52,     3,     6,     7,     8,     9,    13,    14,
      32,    33,    34,    35,    36,    37,    52,    52,    27,     3,
      28,    25,    23,     3,    25,    25,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    25,    25,
      52,    50,    52,    48,    48,     3
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    43,    43,    44,    44,
      45,    45,    46,    47,    47,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    49,    49,    50,
      50,    51,    51,    51,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     8,     1,     1,     1,     0,
       1,     3,     2,     1,     2,     3,     3,     5,     4,     2,
       2,     3,     5,     7,     5,     2,     2,     4,     3,     1,
       3,     1,     1,     1,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: Funcs  */
#line 38 "parser.y"
                { program = yyvsp[0]; }
#line 1237 "parser.tab.c"
    break;

  case 3: /* Funcs: FuncDecl Funcs  */
#line 41 "parser.y"
                      {yyval = yyvsp[-1]; std::dynamic_pointer_cast<ast::Funcs>(yyval)->push_back(std::dynamic_pointer_cast<ast::FuncDecl>(yyvsp[0]));}
#line 1243 "parser.tab.c"
    break;

  case 4: /* Funcs: %empty  */
#line 42 "parser.y"
                   {}
#line 1249 "parser.tab.c"
    break;

  case 5: /* FuncDecl: RetType ID LPAREN Formals RPAREN LBRACE Statements RBRACE  */
#line 45 "parser.y"
                                                                    {yyval = std::make_shared<ast::FuncDecl>(std::dynamic_pointer_cast<ast::ID>(yyvsp[-6]), std::dynamic_pointer_cast<ast::Type>(yyvsp[-7]), std::dynamic_pointer_cast<ast::Formals>(yyvsp[-4]), std::dynamic_pointer_cast<ast::Statements>(yyvsp[-1]));}
#line 1255 "parser.tab.c"
    break;

  case 6: /* RetType: Type  */
#line 48 "parser.y"
              {yyval = yyvsp[0];}
#line 1261 "parser.tab.c"
    break;

  case 7: /* RetType: VOID  */
#line 49 "parser.y"
              {yyval = yyvsp[0];}
#line 1267 "parser.tab.c"
    break;

  case 8: /* Formals: FormalsList  */
#line 52 "parser.y"
                     { yyval = yyvsp[0]; }
#line 1273 "parser.tab.c"
    break;

  case 9: /* Formals: %empty  */
#line 53 "parser.y"
                     {}
#line 1279 "parser.tab.c"
    break;

  case 10: /* FormalsList: FormalDecl  */
#line 56 "parser.y"
                        {yyval = std::make_shared<ast::Formals>(std::dynamic_pointer_cast<ast::Formal>(yyvsp[0]));}
#line 1285 "parser.tab.c"
    break;

  case 11: /* FormalsList: FormalDecl COMMA FormalsList  */
#line 57 "parser.y"
                                          {yyval = yyvsp[0]; std::dynamic_pointer_cast<ast::Formals>(yyval)->push_front( std::dynamic_pointer_cast<ast::Formal>(yyvsp[-2]));}
#line 1291 "parser.tab.c"
    break;

  case 12: /* FormalDecl: Type ID  */
#line 60 "parser.y"
                    {yyval = std::make_shared<ast::Formal>(std::dynamic_pointer_cast<ast::ID>(yyvsp[0]), std::dynamic_pointer_cast<ast::Type>(yyvsp[-1]) );}
#line 1297 "parser.tab.c"
    break;

  case 13: /* Statements: Statement  */
#line 63 "parser.y"
                     {yyval  = std::make_shared<ast::Statements>(std::dynamic_pointer_cast<ast::Statement>(yyvsp[0])); }
#line 1303 "parser.tab.c"
    break;

  case 14: /* Statements: Statements Statement  */
#line 64 "parser.y"
                                  {yyval = yyvsp[-1];  std::dynamic_pointer_cast<ast::Statements>(yyval)->push_back(std::dynamic_pointer_cast<ast::Statement>(yyvsp[0]));}
#line 1309 "parser.tab.c"
    break;

  case 15: /* Statement: LBRACE Statement RBRACE  */
#line 67 "parser.y"
                                   {yyval = yyvsp[-1];}
#line 1315 "parser.tab.c"
    break;

  case 16: /* Statement: Type ID SC  */
#line 68 "parser.y"
                      {yyval = std::make_shared<ast::VarDecl>(std::dynamic_pointer_cast<ast::ID>(yyvsp[-1]), std::dynamic_pointer_cast<ast::Type>(yyvsp[-2]));}
#line 1321 "parser.tab.c"
    break;

  case 17: /* Statement: Type ID ASSIGN Exp SC  */
#line 69 "parser.y"
                                 {yyval = std::make_shared<ast::VarDecl>(std::dynamic_pointer_cast<ast::ID>(yyvsp[-3]), std::dynamic_pointer_cast<ast::Type>(yyvsp[-4]), std::dynamic_pointer_cast<ast::Exp>(yyvsp[-1]));}
#line 1327 "parser.tab.c"
    break;

  case 18: /* Statement: ID ASSIGN Exp SC  */
#line 70 "parser.y"
                            {yyval = std::make_shared<ast::Assign>(std::dynamic_pointer_cast<ast::ID>(yyvsp[-3]), std::dynamic_pointer_cast<ast::Exp>(yyvsp[-1]));}
#line 1333 "parser.tab.c"
    break;

  case 19: /* Statement: Call SC  */
#line 71 "parser.y"
                   {yyval = yyvsp[-1];}
#line 1339 "parser.tab.c"
    break;

  case 20: /* Statement: RETURN SC  */
#line 72 "parser.y"
                     {yyval = std::make_shared<ast::Return>();}
#line 1345 "parser.tab.c"
    break;

  case 21: /* Statement: RETURN Exp SC  */
#line 73 "parser.y"
                         { yyval = std::make_shared<ast::Return>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-1]));}
#line 1351 "parser.tab.c"
    break;

  case 22: /* Statement: IF LPAREN Exp RPAREN Statement  */
#line 74 "parser.y"
                                          {yyval = std::make_shared<ast::If>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-2]), std::dynamic_pointer_cast<ast::Statement>(yyvsp[0]));}
#line 1357 "parser.tab.c"
    break;

  case 23: /* Statement: IF LPAREN Exp RPAREN Statement ELSE Statement  */
#line 75 "parser.y"
                                                         {yyval = std::make_shared<ast::If>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-4]), std::dynamic_pointer_cast<ast::Statement>(yyvsp[-2]), std::dynamic_pointer_cast<ast::Statement>(yyvsp[0]));}
#line 1363 "parser.tab.c"
    break;

  case 24: /* Statement: WHILE LPAREN Exp RPAREN Statement  */
#line 76 "parser.y"
                                             {yyval = std::make_shared<ast::While>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-2]), std::dynamic_pointer_cast<ast::Statement>(yyvsp[0]));}
#line 1369 "parser.tab.c"
    break;

  case 25: /* Statement: BREAK SC  */
#line 77 "parser.y"
                    {yyval =yyvsp[-1];}
#line 1375 "parser.tab.c"
    break;

  case 26: /* Statement: CONTINUE SC  */
#line 78 "parser.y"
                       {yyval = yyvsp[-1];}
#line 1381 "parser.tab.c"
    break;

  case 27: /* Call: ID LPAREN ExpList RPAREN  */
#line 81 "parser.y"
                               {yyval = std::make_shared<ast::Call>(std::dynamic_pointer_cast<ast::ID>(yyvsp[-3]), std::dynamic_pointer_cast<ast::ExpList>(yyvsp[-1]));}
#line 1387 "parser.tab.c"
    break;

  case 28: /* Call: ID LPAREN RPAREN  */
#line 82 "parser.y"
                       {yyval = std::make_shared<ast::Call>(std::dynamic_pointer_cast<ast::ID>(yyvsp[-2]));}
#line 1393 "parser.tab.c"
    break;

  case 29: /* ExpList: Exp  */
#line 85 "parser.y"
             {yyval = std::make_shared<ast::ExpList>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[0]));}
#line 1399 "parser.tab.c"
    break;

  case 30: /* ExpList: Exp COMMA ExpList  */
#line 86 "parser.y"
                           { yyval = yyvsp[0]; std::dynamic_pointer_cast<ast::ExpList>(yyval)->push_front(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-2]));}
#line 1405 "parser.tab.c"
    break;

  case 31: /* Type: INT  */
#line 89 "parser.y"
          { yyval = yyvsp[0];}
#line 1411 "parser.tab.c"
    break;

  case 32: /* Type: BYTE  */
#line 90 "parser.y"
           { yyval = yyvsp[0];}
#line 1417 "parser.tab.c"
    break;

  case 33: /* Type: BOOL  */
#line 91 "parser.y"
           { yyval = yyvsp[0];}
#line 1423 "parser.tab.c"
    break;

  case 34: /* Exp: LPAREN Exp RPAREN  */
#line 95 "parser.y"
                       {yyval = yyvsp[-1];}
#line 1429 "parser.tab.c"
    break;

  case 35: /* Exp: Exp ADD Exp  */
#line 96 "parser.y"
                 {yyval = std::make_shared<ast::BinOp>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-2]), std::dynamic_pointer_cast<ast::Exp>(yyvsp[0]), ast::BinOpType::ADD);}
#line 1435 "parser.tab.c"
    break;

  case 36: /* Exp: Exp SUB Exp  */
#line 97 "parser.y"
                 {yyval = std::make_shared<ast::BinOp>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-2]), std::dynamic_pointer_cast<ast::Exp>(yyvsp[0]), ast::BinOpType::SUB);}
#line 1441 "parser.tab.c"
    break;

  case 37: /* Exp: Exp MUL Exp  */
#line 98 "parser.y"
                 {yyval = std::make_shared<ast::BinOp>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-2]), std::dynamic_pointer_cast<ast::Exp>(yyvsp[0]), ast::BinOpType::MUL);}
#line 1447 "parser.tab.c"
    break;

  case 38: /* Exp: Exp DIV Exp  */
#line 99 "parser.y"
                 {yyval = std::make_shared<ast::BinOp>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-2]), std::dynamic_pointer_cast<ast::Exp>(yyvsp[0]), ast::BinOpType::DIV);}
#line 1453 "parser.tab.c"
    break;

  case 39: /* Exp: ID  */
#line 100 "parser.y"
        { yyval = yyvsp[0];}
#line 1459 "parser.tab.c"
    break;

  case 40: /* Exp: Call  */
#line 101 "parser.y"
          {yyval = yyvsp[0];}
#line 1465 "parser.tab.c"
    break;

  case 41: /* Exp: NUM  */
#line 102 "parser.y"
         {yyval = yyvsp[0];}
#line 1471 "parser.tab.c"
    break;

  case 42: /* Exp: NUM_B  */
#line 103 "parser.y"
           {yyval = yyvsp[0];}
#line 1477 "parser.tab.c"
    break;

  case 43: /* Exp: STRING  */
#line 104 "parser.y"
            {yyval = yyvsp[0];}
#line 1483 "parser.tab.c"
    break;

  case 44: /* Exp: TRUE  */
#line 105 "parser.y"
          {yyval = yyvsp[0];}
#line 1489 "parser.tab.c"
    break;

  case 45: /* Exp: FALSE  */
#line 106 "parser.y"
           {yyval = yyvsp[0];}
#line 1495 "parser.tab.c"
    break;

  case 46: /* Exp: NOT Exp  */
#line 107 "parser.y"
             { yyval = std::make_shared<ast::Not>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[0])); }
#line 1501 "parser.tab.c"
    break;

  case 47: /* Exp: Exp AND Exp  */
#line 108 "parser.y"
                 { yyval = std::make_shared<ast::And>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-2]), std::dynamic_pointer_cast<ast::Exp>(yyvsp[0])); }
#line 1507 "parser.tab.c"
    break;

  case 48: /* Exp: Exp OR Exp  */
#line 109 "parser.y"
                { yyval = std::make_shared<ast::Or>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-2]), std::dynamic_pointer_cast<ast::Exp>(yyvsp[0])); }
#line 1513 "parser.tab.c"
    break;

  case 49: /* Exp: Exp EQ Exp  */
#line 110 "parser.y"
                                {yyval = std::make_shared<ast::RelOp>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-2]), std::dynamic_pointer_cast<ast::Exp>(yyvsp[0]),ast::RelOpType::EQ); }
#line 1519 "parser.tab.c"
    break;

  case 50: /* Exp: Exp NE Exp  */
#line 111 "parser.y"
                                {yyval = std::make_shared<ast::RelOp>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-2]), std::dynamic_pointer_cast<ast::Exp>(yyvsp[0]),ast::RelOpType::NE); }
#line 1525 "parser.tab.c"
    break;

  case 51: /* Exp: Exp LT Exp  */
#line 112 "parser.y"
                                {yyval = std::make_shared<ast::RelOp>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-2]), std::dynamic_pointer_cast<ast::Exp>(yyvsp[0]),ast::RelOpType::LT); }
#line 1531 "parser.tab.c"
    break;

  case 52: /* Exp: Exp GT Exp  */
#line 113 "parser.y"
                                {yyval = std::make_shared<ast::RelOp>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-2]), std::dynamic_pointer_cast<ast::Exp>(yyvsp[0]),ast::RelOpType::GT); }
#line 1537 "parser.tab.c"
    break;

  case 53: /* Exp: Exp LE Exp  */
#line 114 "parser.y"
                                {yyval = std::make_shared<ast::RelOp>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-2]), std::dynamic_pointer_cast<ast::Exp>(yyvsp[0]),ast::RelOpType::LE); }
#line 1543 "parser.tab.c"
    break;

  case 54: /* Exp: Exp GE Exp  */
#line 115 "parser.y"
                                {yyval = std::make_shared<ast::RelOp>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[-2]), std::dynamic_pointer_cast<ast::Exp>(yyvsp[0]),ast::RelOpType::GE); }
#line 1549 "parser.tab.c"
    break;

  case 55: /* Exp: LPAREN Type RPAREN Exp  */
#line 116 "parser.y"
                                   {yyval = std::make_shared<ast::Cast>(std::dynamic_pointer_cast<ast::Exp>(yyvsp[0]), std::dynamic_pointer_cast<ast::Type>(yyvsp[-2])); }
#line 1555 "parser.tab.c"
    break;


#line 1559 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 121 "parser.y"


void yyerror(const char*){
    output::errorSyn(yylineno);
       exit(0);
}
// TODO: Place any additional code here
