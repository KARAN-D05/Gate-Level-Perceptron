# 🕵️‍♂️ Detector-V0.2
- Correctly detects patterns and clasifies them as one of:-
   - Equivalence: Input pattern exactly matches the weight pattern
     - A<sub>rc</sub> = W<sub>rc</sub>
   - Sub-pattern: Input pattern is a subset of weight pattern
     - A<sub>rc</sub> ⊂ W<sub>rc</sub>  
   - Super-pattern: Input pattern is a superset of weight pattern
     - A<sub>rc</sub> ⊃ W<sub>rc</sub>
   - Anti-pattern: Input pattern is neither sub-pattern nor super-pattern nor equivalence of weight pattern
     - A<sub>rc</sub> ⊈ W<sub>rc</sub> ∧ A<sub>rc</sub> ⊉ W<sub>rc</sub> ∨ A<sub>rc</sub> ∩ W<sub>rc</sub> = ∅ ∨ A<sub>rc</sub> ∩ W<sub>rc</sub> ≠ ∅ 

<p align="center">
  <img src="Images/super pattern.png" alt="Pattern Detector Output" width="1000">
</p>

<p align="center">
  Detector recognize super-pattern
</p>

## ⚙️Mechanism
- It uses the two independent Point of views of [Detector_v0.0](../Detector_v0.0) and [Detector_v0.1](../Detector_v0.1) for final decison making.
  - Detector_v0.0 recognizes equivalence and sub-patterns: EQ-SUB Recognition
  - Detector_v0.1 recognizes equivalence and super-patterns: EQ-SUPER Recognition
- For same weights for a given input pattern, Detector_v0.0 and Detector_v0.1 make decisions based on their internal architecture, the **intermediate decision making stage**
- Let R<sub>0</sub> represent recognition and R̅<sub>0</sub> represent derecognition by Detector_v0.0.
- Let R<sub>1</sub> represent recognition and R̅<sub>1</sub> represent derecognition by Detector_v0.1.
- Final Decision making stage:
   - Logical Analyzer
        - R<sub>0</sub>R<sub>1</sub>, represent both POVs recognize the input pattern, hence suggesting it is Equivalence, as it is the only common intersection on which they can agree upon.
        - R̅<sub>0</sub>R<sub>1</sub>, represent only Detector_v0.1 recognizing the input pattern, hence a super-pattern.
        - R<sub>0</sub>R̅<sub>1</sub>, represent only Detector_v0.0 recognizing the input pattern, hence a sub-pattern.
        - R̅<sub>0</sub>R̅<sub>1</sub>, represent both POVs derecognizing the input pattern, hence suggesting it is neither sub-pattern nor super-pattern nor equivalence, thus an anti-pattern. 

<p align="center">
  <img src="Images/anti pattern.png" alt="Pattern Detector Output" width="1000">
</p>

<p align="center">
  Detector recognize anti-pattern
</p>

## ⚠️Limitations
- No learning or adaptation, weight grid is fixed and never changes based on experience.
- No generalization, shifted or  structurally similar patterns are treated as different.
- Rigid decision boundaries.
- No memory of past inputs

## ✔ Why this is not Self-learning Intelligence or a Perceptron:
- A perceptron evaluates degrees of similarity and adapts over time, while this system uses the embedded intelligence of its architecture to make decisons. Our machine can reason but not improve.
- This system exhibits embedded intelligence: it can reason about and classify relationships between patterns using fix logical rules. However, it is not a self-learning system.

