#include<iostream>
#include<vector>
#include<string>
using namespace std;
/* ---------- Education Class ---------- */
class Education{
public:
    string degree;
    string institute;
    int year;
    void input(){
        cout << "Enter degree: ";
        getline(cin, degree);
        cout << "Enter institute: ";
        getline(cin, institute);
        cout << "Enter year: ";
        cin >> year;
        cin.ignore();
    }
    void display() const{
        cout << degree << " | " << institute << " | " << year << endl;
    }
};
/* ---------- Resume Class ---------- */
class Resume{
    string name, email, phone;
    vector<Education> educationList;
    vector<string> skills;
public:
    void inputPersonalInfo(){
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Email: ";
        getline(cin, email);
        cout << "Enter Phone: ";
        getline(cin, phone);
    }
    void inputEducation(){
        int n;
        cout << "How many education entries? ";
        cin >> n;
        cin.ignore();
        for(int i = 0; i<n; i++){
            Education e;
            cout << "\nEducation " << i + 1 << endl;
            e.input();
            educationList.push_back(e);
        }
    }
    void inputSkills(){
        int n;
        cout << "How many skills? ";
        cin >> n;
        cin.ignore();
        for(int i = 0; i < n; i++){
            string skill;
            cout << "Enter skill: ";
            getline(cin, skill);
            skills.push_back(skill);
        }
    }
    void displayResume() const{
        cout << "\n========== RESUME ==========\n";
        cout << "Name  : " << name << endl;
        cout << "Email : " << email << endl;
        cout << "Phone : " << phone << endl;
        cout << "\n--- EDUCATION ---\n";
        for(const auto& e : educationList)
            e.display();
        cout << "\n--- SKILLS ---\n";
        for(const auto& s : skills)
            cout << "- " << s << endl;
    }
};
/* ---------- Main ---------- */
int main(){
    Resume r;
    cout << "===== SIMPLE RESUME BUILDER =====\n\n";
    r.inputPersonalInfo();
    r.inputEducation();
    r.inputSkills();
    r.displayResume();
    return 0;
}
