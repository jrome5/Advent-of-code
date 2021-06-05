using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;

namespace Advent17
{
    class Rule
    {
        char target = ' ';
        List<int> rules;

        public Rule()
        {
            rules = new List<int>();
        }

        public Rule(char target, List<int> rules)
        {
            this.target = target;
            this.rules = new List<int>(rules);
        }

        public void AddTarget(char target)
        {
            this.target = target;
        }

        /*
         * Add rule to left or right variable. return true if full
         */
        public void AddRule(int rule)
        {
            rules.Add(rule);
        }

        public char GetTarget()
        {
            return target;
        }

        public List<int> GetRules()
        {
            return rules;
        }

        public void ClearRule()
        {
            target = ' ';
            rules.Clear();
        }

        public bool isTargetRule()
        {
            return target != ' ';
        }

        public Rule Copy()
        {
            return new Rule(target, rules);
        }
    }
    class Program
    {
        static int checkLine(String line, Dictionary<int, List<Rule>> rules, int rule_no, int index)
        {
            bool isTargetRule = rules[rule_no][0].isTargetRule(); //start index will be target if true
            if (isTargetRule)
            {
                Rule rule = rules[rule_no][0];
                char c = Char.Parse(line.Substring(index, 1));
                char v = rule.GetTarget();
                return c == v ? index+1: 0;
            }
            else
            {
                foreach (Rule rule in rules[rule_no])
                {
                    int tmp = index;
                    bool success = true;
                    foreach (var subrules in rule.GetRules())
                    {
                        int new_val = checkLine(line, rules, subrules, tmp);
                        if (new_val > tmp)
                        {
                            tmp = new_val;
                        }
                        else
                        {
                            success = false;
                            break;
                        }
                    }
                    if(success)
                    {
                        return tmp;
                    }
                }
                return index;
            }
        }
        static void Main(string[] args)
        {
            try
            {
                // Get the current directory.
                string path = Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), @"..\..\..\input.txt");
                string[] files = File.ReadAllLines(path);
                Dictionary<int, List<Rule>> rules = new Dictionary<int, List<Rule>>();
                bool readRules = true;
                int count = 0;
                foreach (string line in files)
                {
                    if (readRules)
                    {
                        if(line == "")
                        {
                            readRules = false;
                            continue;
                        }
                        int colon_index = line.IndexOf(':');
                        int rule_no = Int32.Parse(line.Substring(0, colon_index));
                        List<Rule> sub_rules = new List<Rule>();
                        string sub_line = line.Substring(colon_index + 1, line.Length - (colon_index + 1)); //ignore colon
                        string[] words = sub_line.Split(' ');
                        Rule rule = new Rule();
                        bool rules_to_add = false;
                        foreach (string word in words)
                        {
                            int value = 0;
                            int target_index = word.IndexOf('\"') + 1; //target will be 1 after a quote mark
                            if (target_index > 0) //rule is a target rule
                            {
                                char target = Char.Parse(word.Substring(target_index, 1));
                                rule.AddTarget(target);
                                var tmp = rule.Copy();
                                sub_rules.Add(tmp);
                                rule.ClearRule();
                            }
                            else if (Int32.TryParse(word, out value))
                            {
                                rule.AddRule(value);
                                rules_to_add = true;
                            }
                            else
                            {
                                if(rules_to_add)
                                {
                                    var tmp = rule.Copy();
                                    sub_rules.Add(tmp);
                                    rule.ClearRule();
                                    rules_to_add = false;
                                }
                              
                            }
                        }
                        if(rules_to_add)
                        {
                            var tmp = rule.Copy();
                            sub_rules.Add(tmp);
                            rule.ClearRule();
                            rules_to_add = false;
                        }
                        rules.Add(rule_no, sub_rules);
                    }
                    else
                    {
                        bool valid = true;
                        int curr_index = 0;
                        foreach (var rule in rules[0][0].GetRules())
                        {
                            int index = checkLine(line, rules, rule, curr_index);
                            if (curr_index  == index && index != 0)//unprogressed
                            {
                                valid = false;
                                break;
                            }
                            curr_index = index;
                        }
                        if (curr_index != line.Length)
                            valid = false; //unmatched characters
                        count += valid ? 1 : 0; //add if true
                    }
                }
                Console.WriteLine(count);
            }
            catch (Exception e)
            {
                Console.WriteLine("The process failed: {0}", e.ToString());
            }
        }
    }
}
