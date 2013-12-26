#include <fl/Headers.h>

int main(int argc, char** argv){
fl::Engine* engine = new fl::Engine;
engine->setName("Sugeno-Tip-Calculator");

fl::InputVariable* inputVariable1 = new fl::InputVariable;
inputVariable1->setEnabled(true);
inputVariable1->setName("FoodQuality");
inputVariable1->setRange(1.00000000, 10.00000000);
inputVariable1->addTerm(new fl::Trapezoid("Bad", 0.00000000, 1.00000000, 3.00000000, 7.00000000));
inputVariable1->addTerm(new fl::Trapezoid("Good", 3.00000000, 7.00000000, 10.00000000, 11.00000000));
engine->addInputVariable(inputVariable1);

fl::InputVariable* inputVariable2 = new fl::InputVariable;
inputVariable2->setEnabled(true);
inputVariable2->setName("Service");
inputVariable2->setRange(1.00000000, 10.00000000);
inputVariable2->addTerm(new fl::Trapezoid("Bad", 0.00000000, 1.00000000, 3.00000000, 7.00000000));
inputVariable2->addTerm(new fl::Trapezoid("Good", 3.00000000, 7.00000000, 10.00000000, 11.00000000));
engine->addInputVariable(inputVariable2);

fl::OutputVariable* outputVariable1 = new fl::OutputVariable;
outputVariable1->setEnabled(true);
outputVariable1->setName("CheapTip");
outputVariable1->setRange(5.00000000, 25.00000000);
outputVariable1->setLockOutputRange(false);
outputVariable1->setDefaultValue(fl::nan);
outputVariable1->setLockValidOutput(false);
outputVariable1->setDefuzzifier(new fl::WeightedAverage);
outputVariable1->fuzzyOutput()->setAccumulation(new fl::AlgebraicSum);
outputVariable1->addTerm(new fl::Constant("Low", 10.00000000));
outputVariable1->addTerm(new fl::Constant("Medium", 15.00000000));
outputVariable1->addTerm(new fl::Constant("High", 20.00000000));
engine->addOutputVariable(outputVariable1);

fl::OutputVariable* outputVariable2 = new fl::OutputVariable;
outputVariable2->setEnabled(true);
outputVariable2->setName("AverageTip");
outputVariable2->setRange(5.00000000, 25.00000000);
outputVariable2->setLockOutputRange(false);
outputVariable2->setDefaultValue(fl::nan);
outputVariable2->setLockValidOutput(false);
outputVariable2->setDefuzzifier(new fl::WeightedAverage);
outputVariable2->fuzzyOutput()->setAccumulation(new fl::AlgebraicSum);
outputVariable2->addTerm(new fl::Constant("Low", 10.00000000));
outputVariable2->addTerm(new fl::Constant("Medium", 15.00000000));
outputVariable2->addTerm(new fl::Constant("High", 20.00000000));
engine->addOutputVariable(outputVariable2);

fl::OutputVariable* outputVariable3 = new fl::OutputVariable;
outputVariable3->setEnabled(true);
outputVariable3->setName("GenerousTip");
outputVariable3->setRange(5.00000000, 25.00000000);
outputVariable3->setLockOutputRange(false);
outputVariable3->setDefaultValue(fl::nan);
outputVariable3->setLockValidOutput(false);
outputVariable3->setDefuzzifier(new fl::WeightedAverage);
outputVariable3->fuzzyOutput()->setAccumulation(new fl::AlgebraicSum);
outputVariable3->addTerm(new fl::Constant("Low", 10.00000000));
outputVariable3->addTerm(new fl::Constant("Medium", 15.00000000));
outputVariable3->addTerm(new fl::Constant("High", 20.00000000));
engine->addOutputVariable(outputVariable3);

fl::RuleBlock* ruleBlock = new fl::RuleBlock;
ruleBlock->setEnabled(true);
ruleBlock->setName("");
ruleBlock->setConjunction(new fl::EinsteinProduct);
ruleBlock->setDisjunction(new fl::EinsteinSum);
ruleBlock->setActivation(new fl::AlgebraicProduct);
ruleBlock->addRule(fl::Rule::parse("if FoodQuality is extremely Bad and Service is extremely Bad then CheapTip is extremely Low and AverageTip is very Low and GenerousTip is Low", engine));
ruleBlock->addRule(fl::Rule::parse("if FoodQuality is Good and Service is extremely Bad then CheapTip is Low and AverageTip is Low and GenerousTip is Medium", engine));
ruleBlock->addRule(fl::Rule::parse("if FoodQuality is very Good and Service is very Bad then CheapTip is Low and AverageTip is Medium and GenerousTip is High", engine));
ruleBlock->addRule(fl::Rule::parse("if FoodQuality is Bad and Service is Bad then CheapTip is Low and AverageTip is Low and GenerousTip is Medium", engine));
ruleBlock->addRule(fl::Rule::parse("if FoodQuality is Good and Service is Bad then CheapTip is Low and AverageTip is Medium and GenerousTip is High", engine));
ruleBlock->addRule(fl::Rule::parse("if FoodQuality is extremely Good and Service is Bad then CheapTip is Low and AverageTip is Medium and GenerousTip is very High", engine));
ruleBlock->addRule(fl::Rule::parse("if FoodQuality is Bad and Service is Good then CheapTip is Low and AverageTip is Medium and GenerousTip is High", engine));
ruleBlock->addRule(fl::Rule::parse("if FoodQuality is Good and Service is Good then CheapTip is Medium and AverageTip is Medium and GenerousTip is very High", engine));
ruleBlock->addRule(fl::Rule::parse("if FoodQuality is very Bad and Service is very Good then CheapTip is Low and AverageTip is Medium and GenerousTip is High", engine));
ruleBlock->addRule(fl::Rule::parse("if FoodQuality is very very Good and Service is very very Good then CheapTip is High and AverageTip is very High and GenerousTip is extremely High", engine));
engine->addRuleBlock(ruleBlock);


}
