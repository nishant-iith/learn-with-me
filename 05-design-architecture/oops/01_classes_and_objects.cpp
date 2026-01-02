#include <iostream>
#include <list>
using namespace std;

class YoutubeChannel {
private:
    string Name;
    int SubscribersCount;
    list<string> PublishedVideoTitles;
protected:
    string OwnerName;
    int ContentQuality;
public:
    void SetName(string name){
        Name = name;
    }
    string GetName(){
        return Name;
    }
    void SetOwnerName(string ownerName){
        OwnerName = ownerName;
    }
    string GetOwnerName(){
        return OwnerName;
    }
    void Subscribe(){
        SubscribersCount++;
    }
    void Unsubscribe(){
        if(SubscribersCount>0) SubscribersCount--;
    }

    void PublishVideo(string title){
        PublishedVideoTitles.push_back(title);
    }

    YoutubeChannel(string Name, string OwnerName){
        this->Name = Name;
        this->OwnerName = OwnerName;
        this->SubscribersCount = 0;
        this->ContentQuality = 0;
    }

    void GetInfo(){
        cout << "Channel Name: "<<Name<<endl;
        cout << "Owner Name: "<<OwnerName<<endl;
        cout << "Subscribers: "<<SubscribersCount<<endl;
        cout << "Content Quality: "<<ContentQuality<<endl;
        cout << "Published Videos: "<<endl;
        for(string videoTitle : PublishedVideoTitles){
            cout<<"- "<<videoTitle<<endl;
        }
    }
};

class CookingYoutubeChannel : public YoutubeChannel {
public:
    int RecipesCount;
    CookingYoutubeChannel(string Name, string OwnerName) : YoutubeChannel(Name, OwnerName) {

    }

    void Practice(){
        cout<< OwnerName << " is practicing cooking, learning new recipes, experimenting with flavors..." << endl;
        ContentQuality++;
    }
};

class SingingYoutubeChannel : public YoutubeChannel {
public:
    int SongsCount;
    SingingYoutubeChannel(string Name, string OwnerName) : YoutubeChannel(Name, OwnerName) {

    }

    void Practice(){
        cout<< OwnerName << " is practicing singing, learning new songs, improving vocal techniques..." << endl;
        ContentQuality++;
    }
};

int main(){
    // YoutubeChannel ytch1("CodeBeauty", "Jane Doe");
    // ytch1.PublishVideo("C++ Basics");
    // ytch1.PublishVideo("OOP in C++");
    // ytch1.PublishVideo("STL in C++");
    // ytch1.Subscribe();
    // ytch1.Subscribe();
    // ytch1.GetInfo();

    CookingYoutubeChannel cookingYtCh("FoodieFun", "John Smith");
    SingingYoutubeChannel singingYtCh("MelodyMagic", "Alice Johnson");
    cookingYtCh.PublishVideo("10 Easy Pasta Recipes");
    singingYtCh.PublishVideo("Top 5 Pop Songs Cover");
    cookingYtCh.Subscribe();
    singingYtCh.Subscribe();
    cookingYtCh.Practice();
    singingYtCh.Practice();
    cookingYtCh.Practice();
    cookingYtCh.Practice();
    cookingYtCh.GetInfo();
    singingYtCh.GetInfo();
    return 0;
}