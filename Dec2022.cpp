//importing necessary libraries
#include<iostream>
#include <map>
#include<vector>

// created a class Dice with methods to define movement on the grid.

class Dice{
    public:
        std::map<int,float> _dice;
        std::vector<float> _prev;
        float _top,_bottom,_right,_left,_front,_back;
        int _step;
        int _x,_y;
        Dice(float value){
            for (int  i = 1; i <=6; i++){
                _dice[i]=0;
            }
            _prev.push_back(0);
            _top=1;
            _bottom=2;
            _right=5;
            _left=3;
            _front=6;
            _back=4;
            _step=0;
            _dice[_top]=value;
            _x=0;
            _y=0;
        }
        Dice(){

        }

        ~Dice(){
            
        }

        bool moveRight(float value){
            _step++;
            if (_dice[_left]==0){
                _dice[_left]=(value-_prev.back())/_step;
            }
            else if (abs(_dice[_left]-(value-_prev.back())/_step)>0.2){
                return 0;
            }
            if (_x==0){
                return 0;
            }
            else{
                _x-=1;
            }
            int changed=_bottom;
            _bottom=_right;
            _right=_top;
            _top=_left;
            _left=changed;
            _prev.push_back(value);
            return 1;
            
        }
        bool moveLeft(float value){
            _step++;
            if (_dice[_right]==0){
               _dice[_right]=(value-_prev.back())/_step;
            }
            else if (abs(_dice[_right]-(value-_prev.back())/_step)>0.2){
                return 0;
            }
            if (_x==5){
                return 0;
            }
            else{
                _x+=1;
            }
            int changed=_bottom;
            _bottom=_left;
            _left=_top;
            _top=_right;
            _right=changed;
            _prev.push_back(value);
            return 1;
        }
        bool moveUp(float value){
            _step++;
            if (_dice[_front]==0){
                _dice[_front]=(value-_prev.back())/_step;
            }
            else if (abs(_dice[_front]-(value-_prev.back())/_step)>0.2){
                return 0;
            }
            if (_y==5){
                return 0;
            }
            else{
                _y+=1;
            }
            int changed=_bottom;
            _bottom=_back;
            _back=_top;
            _top=_front;
            _front=changed;
            _prev.push_back(value);
            return 1;
            
        }
        bool moveDown(float value){
            _step++;
            if (_dice[_back]==0){
                _dice[_back]=(value-_prev.back())/_step;
            }
            else if (abs(_dice[_back]-(value-_prev.back())/_step)>0.4){
                return 0;
            }
            if (_y==0){
                return 0;
            }
            else{
                _y-=1;
            }
            int changed=_bottom;
            _bottom=_front;
            _front=_top;
            _top=_back;
            _back=changed;
            _prev.push_back(value);
            return 1;
        }
};
int main(){
    std::vector<Dice> dices;
    float grid[6][6]={
        {0,77,32,403,337,452},
        {5,23,-4,592,445,620},
        {-7,2,357,452,317,395},
        {186,42,195,704,452,228},
        {81,123,240,443,353,508},
        {57,33,132,268,492,732}
    };
    // generating all possible dices and deleting if using a particular dice leads to conflict with two same numbers at same face
    // if any dice reaches top right without conflicts, loop breaks and prints the path direction
    dices.push_back(Dice(grid[0][0]));
    while (dices.size()){
        std::vector<Dice> newDices;
        Dice temp;
        for (int i=0;i<dices.size();i++){
            temp=dices[i];
            if (temp._x==5 && temp._y==5){
                std::cout<<"Path: ";
                for (int j=0;j<temp._prev.size();j++){
                    std::cout<<temp._prev[j]<<" ";
                }
                std::cout<<std::endl;
                exit(0);
            }
            if (temp._x<5 && temp.moveLeft(grid[temp._y][temp._x+1])){
                newDices.push_back(temp);
            }
            temp=dices[i];
            if (temp._x>0&&temp.moveRight(grid[temp._y][temp._x-1])){
                newDices.push_back(temp);
            }
            temp=dices[i];
            if (temp._y<5&&temp.moveUp(grid[temp._y+1][temp._x])){
                newDices.push_back(temp);
            }
            temp=dices[i];
            if (temp._y>0&&temp.moveDown(grid[temp._y-1][temp._x])){
                newDices.push_back(temp);
            }
        }
        dices=newDices;
    }
    
}