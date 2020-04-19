#include <bits/stdc++.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;


int sum_max,sum_min,operand1_min,operand2_min,operand1_max,operand2_max,spell_off;
vector<vector<vector<int>>> grand_results;

vector<int> generate(int a,int b,int A,int B,int s,int S){
    int a_range = A-a;
    int b_range = B-b;
    int operand1,operand2,ans;
    do{
        operand1 = a + rand()%a_range;
        operand2 = b + rand()%b_range;
    }while((operand1+operand2) > S || (operand1 + operand2) < s );
    return vector<int>{operand1,operand2,operand1+operand2};
}


void play(){
    char cont = 'y';
    int ans;
    while(cont=='y')
    {
        vector<vector<int>> results;
        for(int i=0;i<spell_off;i++){
            vector<int> a_b_sum = generate(operand1_min,operand2_min,operand1_max,operand2_max,sum_min,sum_max);
            cout<<a_b_sum[0]<<" + "<<a_b_sum[1]<<" = ";
            cin>>ans;
            if(ans==a_b_sum[2]){
                a_b_sum.push_back(1);
                a_b_sum.push_back(ans);
                results.push_back(a_b_sum);
            }else{
                a_b_sum.push_back(0);
                a_b_sum.push_back(ans);
                results.push_back(a_b_sum);
            }
        }
        grand_results.push_back(results);
        cout<<"Continue?"<<endl;
        cin>>cont;
    }
}

void display_results(){
    //Overall results
    vector<float> accuracy_iteration;
    for(auto iteration:grand_results){
        //Each iteration of spell
        int correct=0,total=0;
        for(auto spell:iteration){
            correct+=spell[3];
            total++;
        }
        accuracy_iteration.push_back((float)correct/(float)total);
    }
    float mass_accuracy=0,total=0;
    for(float acc:accuracy_iteration){
        mass_accuracy += acc;
        total++;
    }
    mass_accuracy = (float)mass_accuracy/(float)total;
    cout<<mass_accuracy<<endl;
}
int main(){
    cout<<"This program will help you practice calculation. Please edit the configuration file to your calculation power."<<endl;;
    int ans; //To store your answer
    string text;
    ifstream f;
    char equals;

    string s;
    f.open("config.txt",ios::in);
    f>>text>>equals>>sum_max;
    f>>text>>equals>>sum_min;
    f>>text>>equals>>operand1_min;
    f>>text>>equals>>operand2_min;
    f>>text>>equals>>operand1_max;
    f>>text>>equals>>operand2_max;
    f>>text>>equals>>spell_off;
    
    //Display
    cout<<sum_max<<sum_min<<operand1_min<<operand2_min<<operand1_max<<operand2_max<<spell_off;
    //See if constraints are ok or not
    if (operand1_min + operand2_min > sum_max) cout<<"Contraint dont satisfy. Exit."<<endl;
    play();
    display_results();
    
}