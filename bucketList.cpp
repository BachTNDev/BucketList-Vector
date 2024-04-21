// Bach Nguyen
// CECS 325-02
// Prog 5 - Bucket List (vector)
// Due Date: 04/23/2024
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

int globalSwapCount = 0;

class Bucket{
private:
    vector<int> v;
public:
    Bucket(){}
    void generate(int size, int min, int max){
        for (int i = 0; i < size; i++){
            int randInt = min + rand() % (max - min + 1);
            v.push_back(randInt);
        }
    }
    void sort(){
        for (int i = 0; i < v.size(); i++){
            for (int j = i + 1; j < v.size(); j++){
                if (v[j] < v[i]){
                    int temp = v[i];
                    v[i] = v[j];
                    v[j] = temp;

                    globalSwapCount++;
                }
            }
        }
    }
    int size(){
        return v.size();
    }
    int atIndex(int index){
        return v[index];
    }
    void merge(Bucket b){
        vector<int> mergedVector;
        int i = 0 , j = 0;

        while (i < v.size() && j < b.size()){
            if (v[i] <= b.atIndex(j)){
                mergedVector.push_back(v[i++]);
            }
            else{
                mergedVector.push_back(b.atIndex(j++));
            }
        }
        while (i < v.size()){
            mergedVector.push_back(v[i++]);
        }
        while (j < b.size()){
            mergedVector.push_back(b.atIndex(j++));
        }
        v = mergedVector;
    }
};

int main(int argc, char *argv[])
{
    srand(time(0));

    int bucketCount = stoi(argv[1]);
    int bucketSize = stoi(argv[2]);
    int bucketMin = stoi(argv[3]);
    int bucketMax = stoi(argv[4]);
    cout << "Bucket Count:"<<bucketCount<<endl;
    cout << "Bucket Size:"<<bucketSize<<endl;
    cout << "Bucket Min Value:"<<bucketMin<<endl;
    cout << "Bucket Max value:"<<bucketMax<<endl;

    vector<Bucket> list; // create empty Bucket vector

    Bucket *bptr;

    for(int i=0; i<bucketCount; i++) // creating bucketCount Buckets
    {
        bptr = new Bucket; // allocating new Bucket
        bptr->generate(bucketSize, bucketMin, bucketMax);//Bucket::generate(int,int,int,int)
        list.push_back(*bptr); // pushing Bucket onto list
    }
    for (auto it = list.begin(); it != list.end(); it++)
    {
        it->sort(); // Bucket::sort
    }
    Bucket endGame; // create empty Bucket to merge ALL buckets

    while (list.size() > 0) // vector<Bucket>::size()
    {
        endGame.merge(list[0]); // merge first bucket in list into endGame
        list.erase(list.begin()); // erase the first bucket in the list
    }

    // write all the numbers in endGame bucket to a file
    fstream out("bucketList.out", ios::out);

    for(int i=0; i<endGame.size(); i++){
        out << endGame.atIndex(i) << endl;
    }
        
    cout << "Global Swap Count:"<<globalSwapCount<<endl;
    cout << "\nbucketList.out has "<<bucketCount * bucketSize<< " sorted numbers\n";
    return 0;
}
