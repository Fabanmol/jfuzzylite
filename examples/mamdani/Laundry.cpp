#include <fl/Headers.h>

int main(int argc, char** argv){
//C++ code generated with jfuzzylite 6.0.

using namespace fl;

Engine* engine = new Engine;
engine->setName("Laundry");

InputVariable* Load = new InputVariable;
Load->setEnabled(true);
Load->setName("Load");
Load->setRange(0.000, 6.000);
Load->setLockValueInRange(false);
Load->addTerm(Discrete::create("small", 8, 0.000, 1.000, 1.000, 1.000, 2.000, 0.800, 5.000, 0.000));
Load->addTerm(Discrete::create("normal", 6, 3.000, 0.000, 4.000, 1.000, 6.000, 0.000));
engine->addInputVariable(Load);

InputVariable* Dirt = new InputVariable;
Dirt->setEnabled(true);
Dirt->setName("Dirt");
Dirt->setRange(0.000, 6.000);
Dirt->setLockValueInRange(false);
Dirt->addTerm(Discrete::create("low", 6, 0.000, 1.000, 2.000, 0.800, 5.000, 0.000));
Dirt->addTerm(Discrete::create("high", 8, 1.000, 0.000, 2.000, 0.200, 4.000, 0.800, 6.000, 1.000));
engine->addInputVariable(Dirt);

OutputVariable* Detergent = new OutputVariable;
Detergent->setEnabled(true);
Detergent->setName("Detergent");
Detergent->setRange(0.000, 80.000);
Detergent->setLockValueInRange(false);
Detergent->fuzzyOutput()->setAggregation(new Maximum);
Detergent->setDefuzzifier(new MeanOfMaximum(500));
Detergent->setDefaultValue(fl::nan);
Detergent->setLockPreviousValue(false);
Detergent->addTerm(Discrete::create("less_than_usual", 6, 10.000, 0.000, 40.000, 1.000, 50.000, 0.000));
Detergent->addTerm(Discrete::create("usual", 8, 40.000, 0.000, 50.000, 1.000, 60.000, 1.000, 80.000, 0.000));
Detergent->addTerm(Discrete::create("more_than_usual", 4, 50.000, 0.000, 80.000, 1.000));
engine->addOutputVariable(Detergent);

OutputVariable* Cycle = new OutputVariable;
Cycle->setEnabled(true);
Cycle->setName("Cycle");
Cycle->setRange(0.000, 20.000);
Cycle->setLockValueInRange(false);
Cycle->fuzzyOutput()->setAggregation(new Maximum);
Cycle->setDefuzzifier(new MeanOfMaximum(500));
Cycle->setDefaultValue(fl::nan);
Cycle->setLockPreviousValue(false);
Cycle->addTerm(Discrete::create("short", 6, 0.000, 1.000, 10.000, 1.000, 20.000, 0.000));
Cycle->addTerm(Discrete::create("long", 4, 10.000, 0.000, 20.000, 1.000));
engine->addOutputVariable(Cycle);

RuleBlock* ruleBlock = new RuleBlock;
ruleBlock->setEnabled(true);
ruleBlock->setName("");
ruleBlock->setConjunction(new Minimum);
ruleBlock->setDisjunction(new Maximum);
ruleBlock->setImplication(new Minimum);
ruleBlock->setActivation(new General);
ruleBlock->addRule(fl::Rule::parse("if Load is small and Dirt is not high then Detergent is less_than_usual", engine));
ruleBlock->addRule(fl::Rule::parse("if Load is small and Dirt is high then  Detergent is usual", engine));
ruleBlock->addRule(fl::Rule::parse("if Load is normal and Dirt is low then Detergent is less_than_usual", engine));
ruleBlock->addRule(fl::Rule::parse("if Load is normal and Dirt is high then Detergent is more_than_usual", engine));
ruleBlock->addRule(fl::Rule::parse("if Detergent is usual  or Detergent is less_than_usual  then Cycle is short", engine));
ruleBlock->addRule(fl::Rule::parse("if Detergent is more_than_usual  then Cycle is long", engine));
engine->addRuleBlock(ruleBlock);


}
