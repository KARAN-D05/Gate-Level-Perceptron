// ============================================================
//  detector-manual.c
// ------------------------------------------------------------
//  When you build your own hardware, you build your own rules.
//  This machine does not follow any existing pattern detection
//  standard. It was designed from scratch, evolving from a
//  simple binary pixel filter into a scoring-based detector
//  isomorphic to the McCulloch-Pitts Neuron.
//
//  This program is that reference. A manual baked directly
//  into the toolchain so the detector architecture is always
//  one command away, no browser, no file explorer, just run
//  it and get your answer.
//
//  Every time the hardware evolves, the logic evolves.
//  Every time the logic evolves, this manual evolves.
// ------------------------------------------------------------
//  Project  : Gate Level Perceptron - Pattern Detector
//  File     : detector-manual.c
//  Covers   : Detector-V0.0, V0.1, V0.2, V1.0
//  Author   : Karan Diwan
//  Date     : 2026
// ============================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ─────────────────────────────────────────
// ANSI COLOR CODES
// ─────────────────────────────────────────

#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define CYAN        "\033[36m"
#define BOLD_WHITE  "\033[1;37m"
#define BOLD_CYAN   "\033[1;36m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_GREEN  "\033[1;32m"
#define BOLD_RED    "\033[1;31m"

// ─────────────────────────────────────────
// PRINT HELPERS
// ─────────────────────────────────────────

void print_divider() {
    printf(DIM "+------------------------------------------------------+" RESET "\n");
}

void print_header(char *title) {
    print_divider();
    printf(DIM "|" RESET BOLD_CYAN "  %-52s" RESET DIM "|" RESET "\n", title);
    print_divider();
}

void print_section(char *title) {
    printf("\n" BOLD_WHITE " %s" RESET "\n", title);
    printf(DIM " ");
    for (int i = 0; i < (int)strlen(title); i++) printf("-");
    printf(RESET "\n");
}

void print_component(int num, char *name) {
    printf("\n" BOLD_YELLOW " [%d] %s" RESET "\n", num, name);
}

void print_bullet(char *text) {
    printf(GREEN "     * " RESET "%s\n", text);
}

void print_limitation(char *text) {
    printf(YELLOW "     ! " RESET "%s\n", text);
}

void print_arrow(char *key, char *value) {
    printf("       " CYAN "%s" RESET " -> %s\n", key, value);
}

void print_iso(char *left, char *right) {
    printf("   " CYAN "%-22s" RESET " <->  %s\n", left, right);
}

// ─────────────────────────────────────────
// COMPONENT DATABASE (for search)
// ─────────────────────────────────────────

typedef struct {
    char name[30];
    char version[20];
    char function[300];
    char note[300];
} Component;

Component components[] = {
    {
        "Input Grid",
        "V0.0+",
        "A 4x4 grid used to input the pattern, visible through the LED grid.",
        "Arc is the input grid element where 3<=r<=0 and 3<=c<=0. A-W link connects each Arc to its corresponding Wrc."
    },
    {
        "Weight Grid",
        "V0.0+",
        "A 4x4 grid used to configure the machine for detection of a particular pattern.",
        "Uses AND gates with binary weight pins. Acts as a filter. Passes input only if weight=1. Wrc is the weight grid element."
    },
    {
        "Output Grid",
        "V0.0+",
        "A 4x4 grid that shows the filtered output. Orc = Arc AND Wrc.",
        "Output at each pixel is the AND of the input and weight at that position."
    },
    {
        "Decision Maker V0.0",
        "V0.0",
        "Checks equivalence between Input Grid Arc and Output Grid Orc.",
        "XNOR check across all 16 pixels. Recognized if Arc is subset of Wrc. Not recognized if Arc is not subset of Wrc."
    },
    {
        "Decision Maker V0.1",
        "V0.1",
        "Checks equivalence between Weight Grid Wrc and Output Grid Orc.",
        "Sets a lower bound below which pattern cannot be recognized. Recognized if Wrc is subset of Arc."
    },
    {
        "Decision Maker V0.2",
        "V0.2",
        "Combines both V0.0 and V0.1 POVs using a Logical Analyzer.",
        "R0=V0.0 result, R1=V0.1 result. R0R1=Equivalence. R0'R1=Super. R0R1'=Sub. R0'R1'=Anti."
    },
    {
        "Decision Maker V1.0",
        "V1.0",
        "Priority-Encoded Magnitude Comparator. Fires if M > theta.",
        "Pattern Recognized: M > theta. Not Recognized: M <= theta. Threshold set via T-pins T8 T4 T2 T1."
    },
    {
        "XNOR Grid",
        "V0.0+",
        "A 4x4 grid of 16 XNOR logic gates. Each gate performs Arc XNOR Orc.",
        "XNOR goes high if both inputs are equal meaning pixel match. In V1.0 outputs are fed into the population counter."
    },
    {
        "Logical Analyzer",
        "V0.2",
        "Final decision stage in V0.2 that combines R0 and R1 from both POVs.",
        "R0 AND R1 = Equivalence | R0' AND R1 = Super | R0 AND R1' = Sub | R0' AND R1' = Anti-pattern"
    },
    {
        "Population Counter",
        "V1.0",
        "Counts total number of matched pixels M. Built from 64 half-adders.",
        "8 HA split 16 inputs into 8 SUM bits weight 1 and 8 CARRY bits weight 2. Successive compression until single bit per weight. Wallace Tree for parallel faster reduction."
    },
    {
        "Threshold",
        "V1.0",
        "Configurable threshold theta set via T-pins. Range: 0 (0000) to 15 (1111).",
        "T-pins are T8 T4 T2 T1. Example: 1001 sets threshold to 9. Pattern recognized only if M strictly greater than theta."
    },
    {
        "MCP Neuron",
        "V1.0",
        "McCulloch-Pitts Neuron. Sums binary inputs M = A + B and fires if M >= theta.",
        "XNOR inputs = Dendrites | Pop-counter = Cell Body | Decision Maker = Signal firing | Output LED = Axon."
    },
    {
        "Sub-pattern",
        "V0.0",
        "Input pattern is a subset of the weight pattern. Arc is proper subset of Wrc.",
        "Recognized by V0.0 but not V0.1. In V0.2 identified via R0 AND R1'."
    },
    {
        "Super-pattern",
        "V0.1+",
        "Input pattern is a superset of the weight pattern. Arc is proper superset of Wrc.",
        "Recognized by V0.1 but not V0.0. In V0.2 identified via R0' AND R1."
    },
    {
        "Equivalence",
        "V0.0+",
        "Input pattern exactly matches the weight pattern. Arc = Wrc.",
        "Recognized by both V0.0 and V0.1. In V0.2 identified via R0 AND R1."
    },
    {
        "Anti-pattern",
        "V0.2",
        "Input is neither sub nor super nor equal to weight pattern.",
        "Arc not subset of Wrc AND Wrc not subset of Arc OR Arc intersection Wrc = empty. Identified via R0' AND R1'."
    },
    {
        "Half Adder",
        "V1.0",
        "Basic building block of the population counter. Has SUM and CARRY outputs.",
        "If weight of input is W, SUM output has weight W and CARRY output has weight 2W. 64 half-adders make the full population counter."
    },
};

int component_count = 17;

// ─────────────────────────────────────────
// SEARCH HELPER
// ─────────────────────────────────────────

void to_upper(char *str) {
    for (int i = 0; str[i]; i++)
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
}

// ─────────────────────────────────────────
// SEARCH FUNCTION
// ─────────────────────────────────────────

void search(char *query) {
    char q[50];
    strncpy(q, query, 49);
    q[49] = '\0';
    to_upper(q);

    int found = 0;

    printf("\n");
    print_divider();
    printf(BOLD_CYAN "  Search results for: %s" RESET "\n", q);
    print_divider();

    for (int i = 0; i < component_count; i++) {
        char name_upper[30];
        char func_upper[300];
        char note_upper[300];

        strncpy(name_upper, components[i].name,     29);  name_upper[29]  = '\0';
        strncpy(func_upper, components[i].function, 299); func_upper[299] = '\0';
        strncpy(note_upper, components[i].note,     299); note_upper[299] = '\0';

        to_upper(name_upper);
        to_upper(func_upper);
        to_upper(note_upper);

        if (strstr(name_upper, q) ||
            strstr(func_upper, q) ||
            strstr(note_upper, q)) {

            printf("\n");
            printf(BOLD_YELLOW "  Component" RESET " : " BOLD_WHITE "%s" RESET "\n", components[i].name);
            printf(CYAN        "  Version  " RESET " : %s\n", components[i].version);
            printf(            "  Function  : %s\n", components[i].function);
            printf(DIM         "  Notes     : %s" RESET "\n", components[i].note);
            printf(DIM "\n  ------------------------------------------------------" RESET "\n");
            found++;
        }
    }

    if (found == 0)
        printf(BOLD_RED "\n  No results found for '%s'\n" RESET, q);
    else
        printf(BOLD_GREEN "\n  %d result(s) found.\n" RESET, found);

    print_divider();
}

// ─────────────────────────────────────────
// VERSION MANUALS
// ─────────────────────────────────────────

void manual_v00() {
    printf("\n");
    print_header("Detector-V0.0 - Binary Pixel Filter");

    print_section("OVERVIEW");
    printf(" A primitive configurable pattern detection machine\n");
    printf(" built entirely from logic gates. Uses a weight array\n");
    printf(" to filter the input pattern and a decision-making\n");
    printf(" stage to check for exact recognition.\n");

    print_section("COMPONENTS");

    print_component(1, "Input Grid (4x4)");
    printf("     Arc is the input grid element.\n");
    printf("     3 <= r <= 0 and 3 <= c <= 0\n");
    printf("     A-W link connects each Arc to its Wrc.\n");

    print_component(2, "Weight Grid (4x4)");
    printf("     Wrc is the weight grid element.\n");
    printf("     3 <= r <= 0 and 3 <= c <= 0\n");
    printf("     Uses AND gates with binary weight pins.\n");
    printf("     Acts as a filter:\n");
    printf("       " CYAN "Weight = 1" RESET " -> input passes through\n");
    printf("       " CYAN "Weight = 0" RESET " -> input is blocked\n");

    print_component(3, "Output Grid (4x4)");
    printf("     Orc = Arc AND Wrc\n");
    printf("     Shows filtered result of input through weight.\n");

    print_component(4, "Decision Maker");
    printf("     XNOR equivalence check between Input and Output.\n");
    printf("     Check = (A00^O00) AND (A01^O01) AND...AND (A33^O33)\n");
    printf(CYAN "     Check = 1" RESET " -> Pattern Recognized\n");
    printf(CYAN "     Check = 0" RESET " -> Pattern Not Recognized\n");
    printf("\n" BOLD_WHITE "     Mathematical Behaviour:\n" RESET);
    printf("       Recognized     : Arc is subset of Wrc\n");
    printf("       Not Recognized : Arc is not subset of Wrc\n");

    print_section("LIMITATIONS");
    print_limitation("Recognizes sub-patterns and garbage patterns.");
    print_limitation("No scoring or noise tolerance.");
    print_limitation("Expects perfectly clean inputs.");
    print_limitation("Binary pixel filter + comparator only.");

    printf("\n");
    print_divider();
}

void manual_v01() {
    printf("\n");
    print_header("Detector-V0.1 - Super-Pattern Recognition");

    print_section("OVERVIEW");
    printf(" Solves the sub-pattern recognition problem of V0.0.\n");
    printf(" Instead recognizes the exact pattern or super-patterns.\n");
    printf(" Single architectural change in the Decision Maker.\n");

    print_section("COMPONENTS");
    printf(" Input Grid, Weight Grid, Output Grid same as V0.0.\n");
    printf(" Orc = Arc AND Wrc\n");

    print_component(4, "Decision Maker (changed from V0.0)");
    printf("     Now checks equivalence between Weight Grid Wrc\n");
    printf("     and Output Grid Orc.\n");
    printf("     (V0.0 checked Input Arc vs Output Orc)\n");
    printf("     Sets a lower bound below which pattern cannot\n");
    printf("     be recognized.\n");
    printf("     Check = (W00^O00) AND (W01^O01) AND...AND (W33^O33)\n");
    printf(CYAN "     Check = 1" RESET " -> Pattern Recognized\n");
    printf(CYAN "     Check = 0" RESET " -> Pattern Not Recognized\n");

    print_section("MATHEMATICAL BEHAVIOUR");
    printf(BOLD_WHITE "     Recognized:\n" RESET);
    printf("       Orc = Wrc\n");
    printf("       Orc is subset of Arc\n");
    printf("       Wrc is subset of Arc\n");
    printf(BOLD_WHITE "     Not Recognized:\n" RESET);
    printf("       Orc != Wrc\n");
    printf("       Orc is not subset of Arc\n");
    printf("       Wrc is not subset of Arc\n");

    printf("\n");
    print_divider();
}

void manual_v02() {
    printf("\n");
    print_header("Detector-V0.2 - Four-Way Pattern Classifier");

    print_section("OVERVIEW");
    printf(" Combines V0.0 and V0.1 as two independent POVs.\n");
    printf(" Correctly detects and classifies patterns as one of:\n");
    printf("   Equivalence, Sub-pattern, Super-pattern, Anti-pattern\n");

    print_section("MECHANISM");
    printf(" V0.0 POV -> Recognizes Equivalence + Sub-patterns\n");
    printf(" V0.1 POV -> Recognizes Equivalence + Super-patterns\n");
    printf(" For same weights, both POVs make independent decisions\n");
    printf(" based on their internal architecture.\n");
    printf("\n" CYAN " R0  " RESET "= recognition by V0.0\n");
    printf(CYAN " R0' " RESET "= derecognition by V0.0\n");
    printf(CYAN " R1  " RESET "= recognition by V0.1\n");
    printf(CYAN " R1' " RESET "= derecognition by V0.1\n");

    print_section("LOGICAL ANALYZER (Final Decision Stage)");
    printf(CYAN "   R0  AND R1 " RESET " -> " BOLD_WHITE "Equivalence\n" RESET);
    printf("                  Arc = Wrc\n");
    printf(CYAN "   R0  AND R1'" RESET " -> " BOLD_WHITE "Sub-pattern\n" RESET);
    printf("                  Arc is proper subset of Wrc\n");
    printf(CYAN "   R0' AND R1 " RESET " -> " BOLD_WHITE "Super-pattern\n" RESET);
    printf("                  Arc is proper superset of Wrc\n");
    printf(CYAN "   R0' AND R1'" RESET " -> " BOLD_WHITE "Anti-pattern\n" RESET);
    printf("                  Arc not sub/superset of Wrc\n");
    printf("                  OR Arc intersection Wrc = empty\n");

    print_section("WHY THIS IS NOT A PERCEPTRON");
    printf("   A perceptron evaluates degrees of similarity and\n");
    printf("   adapts over time. This system uses embedded\n");
    printf("   intelligence of its architecture to make decisions.\n");
    printf("   Our machine can reason but not improve.\n");

    print_section("LIMITATIONS");
    print_limitation("No learning or adaptation.");
    print_limitation("Weight grid is fixed, never changes.");
    print_limitation("No generalization for shifted patterns.");
    print_limitation("Rigid decision boundaries.");
    print_limitation("No memory of past inputs.");

    printf("\n");
    print_divider();
}

void manual_v10() {
    printf("\n");
    print_header("Detector-V1.0 - POP-Count Based Detector");

    print_section("OVERVIEW");
    printf(" Recognizes pattern if matched pixels M > threshold T.\n");
    printf(" Unlike perfect equivalence check, a threshold is set\n");
    printf(" above which the pattern is recognized, and the\n");
    printf(" threshold can vary.\n");
    printf(" Isomorphic to the McCulloch-Pitts (MCP) Neuron.\n");
    printf(" One step closer to self-learning machines.\n");

    print_section("MCP NEURON");
    printf(" Warren McCulloch and Walter Pitts proposed a simple\n");
    printf(" logical model of a biological neuron:\n");
    printf(BOLD_WHITE "   Biological neuron:\n" RESET);
    printf("     Receives inputs via dendrites.\n");
    printf("     Cell body performs computation.\n");
    printf("     Sends signal through axon if threshold met.\n");
    printf(BOLD_WHITE "   MCP Neuron model:\n" RESET);
    printf("     M = A + B  where A,B are in {0,1}\n");
    printf(CYAN "     M >= theta" RESET " -> Neuron Fires,        Output = 1\n");
    printf(CYAN "     M <  theta" RESET " -> Neuron Doesn't Fire, Output = 0\n");    printf(BOLD_WHITE "   Logic gate implementation:\n" RESET);
    printf("     AND gate: theta = 2\n");
    printf("     OR  gate: theta = 1\n");

    print_section("ISOMORPHISM TO MCP NEURON");
    print_iso("16 XNOR inputs", "Dendrites");
    print_iso("Population Counter", "Cell Body");
    print_iso("Decision Maker", "Signal firing decision");
    print_iso("Output LED", "Axon");

    print_section("COMPONENTS");

    print_component(1, "XNOR Equivalence Grid (4x4)");
    printf("     16 XNOR gates. Each gate: Arc XNOR Orc\n");
    printf("     Gate goes high if both inputs are equal.\n");
    printf("     Outputs fed into the population counter.\n");
    printf(DIM "     Biologically equivalent to: Dendrites\n" RESET);

    print_component(2, "Population Counter");
    printf("     Calculates total matched pixels M.\n");
    printf("     Module made up of 64 half-adders.\n");
    printf("     Based on successive bit compression:\n");
    printf("       8 HA -> 8 SUM (weight 1) + 8 CARRY (weight 2)\n");
    printf("       4 HA -> compresses 8 SUM bits of weight 1\n");
    printf("       Repeats until single bit of each weight remains.\n");
    printf(BOLD_WHITE "     Half Adder weight rule:\n" RESET);
    printf("       If inputs A,B have weight W:\n");
    printf("         SUM  output -> weight W\n");
    printf("         CARRY output -> weight 2W\n");
    printf("     Wallace Tree for parallel faster reduction.\n");
    printf(DIM "     Biologically equivalent to: Cell Body\n" RESET);

    print_component(3, "Decision Maker");
    printf("     Priority-Encoded Magnitude Comparator.\n");
    printf(CYAN "     Pattern Recognized     : " RESET "M > theta\n");
    printf(CYAN "     Pattern Not Recognized : " RESET "M <= theta\n");
    printf(DIM "     Biologically equivalent to: Signal firing\n" RESET);

    print_component(4, "Threshold T-pins");
    printf("     Pins: T8 T4 T2 T1\n");
    printf("     Range : 0 (0000) to 15 (1111)\n");
    printf("     Example: 1001 -> threshold = 9\n");
    printf("     Threshold is adjustable for confidence tuning.\n");

    print_component(5, "Output LED");
    printf("     Fires if M > theta.\n");
    printf(DIM "     Biologically equivalent to: Axon\n" RESET);

    print_section("THRESHOLD EXAMPLES");
    printf(GREEN "   theta=7, M=8 : M > theta  -> " RESET "Pattern RECOGNIZED\n");
    printf(YELLOW "   theta=9, M=8 : M <= theta -> " RESET "Pattern NOT RECOGNIZED\n");
    print_section("PROOF OF CONCEPT");
    printf("   Instead of perfect equivalence, we judge based on\n");
    printf("   score M vs threshold theta. A self-learning machine\n");
    printf("   could adjust theta automatically via feedback until\n");
    printf("   it converges to a value that correctly classifies\n");
    printf("   input patterns.\n");

    printf("\n");
    print_divider();
}

void manual_all() {
    printf("\n");
    print_header("Detector Manual - All Versions");
    printf(CYAN "  V0.0" RESET " -> Binary pixel filter, sub-pattern problem\n");
    printf(CYAN "  V0.1" RESET " -> Fixes V0.0, super-pattern recognition\n");
    printf(CYAN "  V0.2" RESET " -> Four-way classifier combining both POVs\n");
    printf(CYAN "  V1.0" RESET " -> POP-Count, threshold-based, MCP Neuron\n");
    printf(DIM "\n Showing all versions...\n" RESET);
    manual_v00();
    manual_v01();
    manual_v02();
    manual_v10();
}

// ─────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────

int main(int argc, char *argv[]) {

    if (argc >= 3 && strcmp(argv[1], "--search") == 0) {
        search(argv[2]);
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--search") == 0) {
        printf(BOLD_WHITE "Usage  : " RESET "./detector-manual --search <term>\n");
        printf(BOLD_WHITE "Example: " RESET "./detector-manual --search threshold\n");
        return 1;
    }

    char input[20];

    printf("\n");
    print_divider();
    printf(DIM "|" RESET BOLD_CYAN "  %-52s" RESET DIM "|" RESET "\n", "Gate Level Perceptron Manual");
    printf(DIM "|" RESET "  %-52s" DIM "|" RESET "\n", "Pattern Detector Architecture Docs");
    print_divider();
    printf(DIM " Tip: " RESET "search a component directly from terminal:\n");
    printf(CYAN "      ./detector-manual --search threshold\n" RESET);

    while (1) {
        printf("\n" DIM " Available: " RESET
               CYAN "V0.0" RESET " | "
               CYAN "V0.1" RESET " | "
               CYAN "V0.2" RESET " | "
               CYAN "V1.0" RESET " | "
               CYAN "all"  RESET " | "
               CYAN "search" RESET " | "
               CYAN "exit" RESET "\n");
        printf(BOLD_WHITE " Enter version: " RESET);
        scanf("%s", input);

        if (strcmp(input, "V0.0") == 0 || strcmp(input, "v0.0") == 0) {
            manual_v00();
        } else if (strcmp(input, "V0.1") == 0 || strcmp(input, "v0.1") == 0) {
            manual_v01();
        } else if (strcmp(input, "V0.2") == 0 || strcmp(input, "v0.2") == 0) {
            manual_v02();
        } else if (strcmp(input, "V1.0") == 0 || strcmp(input, "v1.0") == 0) {
            manual_v10();
        } else if (strcmp(input, "all") == 0) {
            manual_all();
        } else if (strcmp(input, "search") == 0) {
            char query[50];
            printf(BOLD_WHITE " Enter term to search: " RESET);
            scanf("%s", query);
            search(query);
        } else if (strcmp(input, "exit") == 0) {
            printf(BOLD_GREEN "\n Goodbye!\n" RESET);
            break;
        } else {
            printf(BOLD_RED "\n [ERROR]" RESET " Unknown input '%s'\n", input);
            printf(DIM " Try: V0.0, V0.1, V0.2, V1.0, all, search, exit\n" RESET);
        }
    }

    return 0;
}
