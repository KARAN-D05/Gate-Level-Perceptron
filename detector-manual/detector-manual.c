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
//  Author   : KARAN-D05
//  Date     : 2026
// ============================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

    printf("\n+--------------------------------------------------+\n");
    printf("  Search results for: %s\n", q);
    printf("+--------------------------------------------------+\n");

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

            printf("\n  Component : %s\n", components[i].name);
            printf("  Version   : %s\n",   components[i].version);
            printf("  Function  : %s\n",   components[i].function);
            printf("  Notes     : %s\n",   components[i].note);
            printf("\n  --------------------------------------------------\n");
            found++;
        }
    }

    if (found == 0)
        printf("\n  No results found for '%s'\n", q);
    else
        printf("\n  %d result(s) found.\n", found);

    printf("+--------------------------------------------------+\n");
}

// ─────────────────────────────────────────
// VERSION MANUALS
// ─────────────────────────────────────────

void manual_v00() {
    printf("\n");
    printf("+------------------------------------------------------+\n");
    printf("|        Detector-V0.0 - Binary Pixel Filter           |\n");
    printf("+------------------------------------------------------+\n");

    printf("\n OVERVIEW\n");
    printf(" --------\n");
    printf(" A primitive configurable pattern detection machine\n");
    printf(" built entirely from logic gates. Uses a weight array\n");
    printf(" to filter the input pattern and a decision-making\n");
    printf(" stage to check for exact recognition.\n");

    printf("\n COMPONENTS\n");
    printf(" ----------\n");

    printf("\n [1] Input Grid (4x4)\n");
    printf("     Arc is the input grid element.\n");
    printf("     3 <= r <= 0 and 3 <= c <= 0\n");
    printf("     A-W link connects each Arc to its Wrc.\n");

    printf("\n [2] Weight Grid (4x4)\n");
    printf("     Wrc is the weight grid element.\n");
    printf("     3 <= r <= 0 and 3 <= c <= 0\n");
    printf("     Uses AND gates with binary weight pins.\n");
    printf("     Acts as a filter:\n");
    printf("       Weight = 1 -> input passes through\n");
    printf("       Weight = 0 -> input is blocked\n");

    printf("\n [3] Output Grid (4x4)\n");
    printf("     Orc = Arc AND Wrc\n");
    printf("     Shows filtered result of input through weight.\n");

    printf("\n [4] Decision Maker\n");
    printf("     XNOR equivalence check between Input and Output.\n");
    printf("     Check = (A00^O00) AND (A01^O01) AND...AND (A33^O33)\n");
    printf("     Check = 1 -> Pattern Recognized\n");
    printf("     Check = 0 -> Pattern Not Recognized\n");
    printf("\n     Mathematical Behaviour:\n");
    printf("       Recognized     : Arc is subset of Wrc\n");
    printf("       Not Recognized : Arc is not subset of Wrc\n");

    printf("\n LIMITATIONS\n");
    printf(" -----------\n");
    printf("     * Recognizes sub-patterns and garbage patterns.\n");
    printf("     * No scoring or noise tolerance.\n");
    printf("     * Expects perfectly clean inputs.\n");
    printf("     * Binary pixel filter + comparator only.\n");

    printf("\n+------------------------------------------------------+\n");
}

void manual_v01() {
    printf("\n");
    printf("+------------------------------------------------------+\n");
    printf("|      Detector-V0.1 - Super-Pattern Recognition       |\n");
    printf("+------------------------------------------------------+\n");

    printf("\n OVERVIEW\n");
    printf(" --------\n");
    printf(" Solves the sub-pattern recognition problem of V0.0.\n");
    printf(" Instead recognizes the exact pattern or super-patterns.\n");
    printf(" Single architectural change in the Decision Maker.\n");

    printf("\n COMPONENTS\n");
    printf(" ----------\n");
    printf(" Input Grid, Weight Grid, Output Grid same as V0.0.\n");
    printf(" Orc = Arc AND Wrc\n");

    printf("\n [4] Decision Maker (changed from V0.0)\n");
    printf("     Now checks equivalence between Weight Grid Wrc\n");
    printf("     and Output Grid Orc.\n");
    printf("     (V0.0 checked Input Arc vs Output Orc)\n");
    printf("     Sets a lower bound below which pattern cannot\n");
    printf("     be recognized.\n");
    printf("     Check = (W00^O00) AND (W01^O01) AND...AND (W33^O33)\n");
    printf("     Check = 1 -> Pattern Recognized\n");
    printf("     Check = 0 -> Pattern Not Recognized\n");

    printf("\n MATHEMATICAL BEHAVIOUR\n");
    printf(" ----------------------\n");
    printf("     Recognized:\n");
    printf("       Orc = Wrc\n");
    printf("       Orc is subset of Arc\n");
    printf("       Wrc is subset of Arc\n");
    printf("     Not Recognized:\n");
    printf("       Orc != Wrc\n");
    printf("       Orc is not subset of Arc\n");
    printf("       Wrc is not subset of Arc\n");

    printf("\n+------------------------------------------------------+\n");
}

void manual_v02() {
    printf("\n");
    printf("+------------------------------------------------------+\n");
    printf("|       Detector-V0.2 - Four-Way Pattern Classifier    |\n");
    printf("+------------------------------------------------------+\n");

    printf("\n OVERVIEW\n");
    printf(" --------\n");
    printf(" Combines V0.0 and V0.1 as two independent POVs.\n");
    printf(" Correctly detects and classifies patterns as one of:\n");
    printf("   Equivalence, Sub-pattern, Super-pattern, Anti-pattern\n");

    printf("\n MECHANISM\n");
    printf(" ---------\n");
    printf(" V0.0 POV -> Recognizes Equivalence + Sub-patterns\n");
    printf(" V0.1 POV -> Recognizes Equivalence + Super-patterns\n");
    printf(" For same weights, both POVs make independent decisions\n");
    printf(" based on their internal architecture.\n");
    printf("\n R0  = recognition by V0.0\n");
    printf(" R0' = derecognition by V0.0\n");
    printf(" R1  = recognition by V0.1\n");
    printf(" R1' = derecognition by V0.1\n");

    printf("\n LOGICAL ANALYZER (Final Decision Stage)\n");
    printf(" ----------------------------------------\n");
    printf("   R0  AND R1  -> Equivalence\n");
    printf("                  Arc = Wrc\n");
    printf("   R0  AND R1' -> Sub-pattern\n");
    printf("                  Arc is proper subset of Wrc\n");
    printf("   R0' AND R1  -> Super-pattern\n");
    printf("                  Arc is proper superset of Wrc\n");
    printf("   R0' AND R1' -> Anti-pattern\n");
    printf("                  Arc not sub/superset of Wrc\n");
    printf("                  OR Arc intersection Wrc = empty\n");

    printf("\n WHY THIS IS NOT A PERCEPTRON\n");
    printf(" ----------------------------\n");
    printf("   A perceptron evaluates degrees of similarity and\n");
    printf("   adapts over time. This system uses embedded\n");
    printf("   intelligence of its architecture to make decisions.\n");
    printf("   Our machine can reason but not improve.\n");

    printf("\n LIMITATIONS\n");
    printf(" -----------\n");
    printf("   * No learning or adaptation.\n");
    printf("   * Weight grid is fixed, never changes.\n");
    printf("   * No generalization for shifted patterns.\n");
    printf("   * Rigid decision boundaries.\n");
    printf("   * No memory of past inputs.\n");

    printf("\n+------------------------------------------------------+\n");
}

void manual_v10() {
    printf("\n");
    printf("+------------------------------------------------------+\n");
    printf("|      Detector-V1.0 - POP-Count Based Detector        |\n");
    printf("+------------------------------------------------------+\n");

    printf("\n OVERVIEW\n");
    printf(" --------\n");
    printf(" Recognizes pattern if matched pixels M > threshold T.\n");
    printf(" Unlike perfect equivalence check, a threshold is set\n");
    printf(" above which the pattern is recognized, and the\n");
    printf(" threshold can vary.\n");
    printf(" Isomorphic to the McCulloch-Pitts (MCP) Neuron.\n");
    printf(" One step closer to self-learning machines.\n");

    printf("\n MCP NEURON\n");
    printf(" ----------\n");
    printf(" Warren McCulloch and Walter Pitts proposed a simple\n");
    printf(" logical model of a biological neuron:\n");
    printf("   Biological neuron:\n");
    printf("     Receives inputs via dendrites.\n");
    printf("     Cell body performs computation.\n");
    printf("     Sends signal through axon if threshold met.\n");
    printf("   MCP Neuron model:\n");
    printf("     M = A + B  where A,B are in {0,1}\n");
    printf("     M >= theta -> Neuron Fires,        Output = 1\n");
    printf("     M <  theta -> Neuron Doesn't Fire, Output = 0\n");
    printf("   Logic gate implementation:\n");
    printf("     AND gate: theta = 2\n");
    printf("     OR  gate: theta = 1\n");

    printf("\n ISOMORPHISM TO MCP NEURON\n");
    printf(" -------------------------\n");
    printf("   16 XNOR inputs     <->  Dendrites\n");
    printf("   Population Counter <->  Cell Body\n");
    printf("   Decision Maker     <->  Signal firing decision\n");
    printf("   Output LED         <->  Axon\n");

    printf("\n COMPONENTS\n");
    printf(" ----------\n");

    printf("\n [1] XNOR Equivalence Grid (4x4)\n");
    printf("     16 XNOR gates. Each gate: Arc XNOR Orc\n");
    printf("     Gate goes high if both inputs are equal.\n");
    printf("     Outputs fed into the population counter.\n");
    printf("     Biologically equivalent to: Dendrites\n");

    printf("\n [2] Population Counter\n");
    printf("     Calculates total matched pixels M.\n");
    printf("     Module made up of 64 half-adders.\n");
    printf("     Based on successive bit compression:\n");
    printf("       8 HA -> 8 SUM (weight 1) + 8 CARRY (weight 2)\n");
    printf("       4 HA -> compresses 8 SUM bits of weight 1\n");
    printf("       Repeats until single bit of each weight remains.\n");
    printf("     Half Adder weight rule:\n");
    printf("       If inputs A,B have weight W:\n");
    printf("         SUM  output -> weight W\n");
    printf("         CARRY output -> weight 2W\n");
    printf("     Wallace Tree for parallel faster reduction.\n");
    printf("     Biologically equivalent to: Cell Body\n");

    printf("\n [3] Decision Maker\n");
    printf("     Priority-Encoded Magnitude Comparator.\n");
    printf("     Pattern Recognized     : M > theta\n");
    printf("     Pattern Not Recognized : M <= theta\n");
    printf("     Biologically equivalent to: Signal firing\n");

    printf("\n [4] Threshold T-pins\n");
    printf("     Pins: T8 T4 T2 T1\n");
    printf("     Range : 0 (0000) to 15 (1111)\n");
    printf("     Example: 1001 -> threshold = 9\n");
    printf("     Threshold is adjustable for confidence tuning.\n");

    printf("\n [5] Output LED\n");
    printf("     Fires if M > theta.\n");
    printf("     Biologically equivalent to: Axon\n");

    printf("\n THRESHOLD EXAMPLES\n");
    printf(" ------------------\n");
    printf("   theta=7, M=8 : M > theta  -> Pattern RECOGNIZED\n");
    printf("   theta=9, M=8 : M <= theta -> Pattern NOT RECOGNIZED\n");

    printf("\n PROOF OF CONCEPT\n");
    printf(" ----------------\n");
    printf("   Instead of perfect equivalence, we judge based on\n");
    printf("   score M vs threshold theta. A self-learning machine\n");
    printf("   could adjust theta automatically via feedback until\n");
    printf("   it converges to a value that correctly classifies\n");
    printf("   input patterns.\n");

    printf("\n+------------------------------------------------------+\n");
}

void manual_all() {
    printf("\n");
    printf("+------------------------------------------------------+\n");
    printf("|          Detector Manual - All Versions              |\n");
    printf("+------------------------------------------------------+\n");
    printf("\n  V0.0 -> Binary pixel filter, sub-pattern problem\n");
    printf("  V0.1 -> Fixes V0.0, super-pattern recognition\n");
    printf("  V0.2 -> Four-way classifier combining both POVs\n");
    printf("  V1.0 -> POP-Count, threshold-based, MCP Neuron\n");
    printf("\n Showing all versions...\n");
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
        printf("Usage: ./detector-manual --search <term>\n");
        printf("Example: ./detector-manual --search threshold\n");
        return 1;
    }

    char input[20];

    printf("+------------------------------------------------------+\n");
    printf("|          Gate Level Perceptron Manual                |\n");
    printf("|        Pattern Detector Architecture Docs            |\n");
    printf("+------------------------------------------------------+\n");
    printf(" Tip: search a component directly from terminal:\n");
    printf("      ./detector-manual --search threshold\n");

    while (1) {
        printf("\n Available: V0.0 | V0.1 | V0.2 | V1.0 | all | search | exit\n");
        printf(" Enter version: ");
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
            printf(" Enter term to search: ");
            scanf("%s", query);
            search(query);
        } else if (strcmp(input, "exit") == 0) {
            printf("\n Goodbye!\n");
            break;
        } else {
            printf("\n [ERROR] Unknown input '%s'\n", input);
            printf(" Try: V0.0, V0.1, V0.2, V1.0, all, search, exit\n");
        }
    }

    return 0;
}
