#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <iterator>
#include <fstream>
#include <set>
#define MAX 4039
using namespace std;
class SocialAnalysisNetworkSystem {
private:
	// �洢���ѹ�ϵ 
   	map< int , vector <int> > friendships;
public:
    // ����û�
    void addUser(int userId) {
        friendships[userId] = {};
    }

    // ������ѹ�ϵ
    void addFriendship(int user_a, int user_b) {
        friendships[user_a].push_back(user_b);
        friendships[user_b].push_back(user_a);
    }

    // ��ѯ�û���ֱ����������
    int getDirectFriendCount(int userId) {
        return friendships[userId].size();
    }
    
    // ��ѯ�û��ļ���������� 
    int getGapFriend(int userId) {
    	// ֱ������ 
        vector<int> directFriends = friendships[userId];
        // ������� 
        set<int> gapFriends;
        // ����ÿ������ 
        for(size_t i=0;i<directFriends.size();++i){
        	// ���ѵ����� 
            vector<int> secondDegreeFriends = friendships[directFriends[i]];
            for(size_t j=0;j<secondDegreeFriends.size();++j){
				for (size_t k = 0; k < directFriends.size(); ++k) {
					// ȷ�������û������� 
    				if (directFriends[k] == secondDegreeFriends[j]) {
        				break;
    				}
    				// ȷ�����û����ѵ����� 
    				if (k == directFriends.size() - 1) {
        				gapFriends.insert(secondDegreeFriends[j]);
    				}
				}
			}
        }
        // �ų��û��Լ� 
        return gapFriends.size()-1;
    }

    // ���������û�֮�������罻����
    int getShortestDistance(int startUserId, int targetUserId) {
        // �Լ����Լ��ľ���Ϊ0 
		if (startUserId == targetUserId) {
            return 0;
        }
        // ��¼�������ѹ�ϵ 
        map<int, bool> visited;
        // �ݴ���һ�����ѹ�ϵ 
        queue<pair<int, int> > q;
        q.push({startUserId, 0});
        visited[startUserId] = true;
        while (!q.empty()) {
            pair<int,int> current = q.front();
            q.pop();
            for(size_t i=0;i<friendships[current.first].size();++i){
            	// �ҵ� 
                if (friendships[current.first][i]== targetUserId) {
                    return current.second + 1;
                }
                // û�ҵ���������һ�� 
                if (!visited[friendships[current.first][i]]) {
                    q.push({friendships[current.first][i], current.second + 1});
                    visited[friendships[current.first][i]] = true;
                }
            }
        }
        return INT_MAX;
    }
    
    // ��ѯ��ͬ��������3���û�
	vector<int> recommand(int a) {
        vector<int> directFriends = friendships[a],answer(3,-1),person(3,-1);
        set<int> gapFriends;
        int count;
        size_t index,left;
        // �ҵ����û�a�������1�������û�
        for (size_t i = 0; i < directFriends.size(); ++i) {
            vector<int> secondDegreeFriends = friendships[directFriends[i]];
            for (size_t j = 0; j < secondDegreeFriends.size(); ++j) {
                for (size_t k = 0; k < directFriends.size(); ++k) {
                    if (directFriends[k] == secondDegreeFriends[j]) {
                        break;
                    }
                    if (k == directFriends.size() - 1) {
                        gapFriends.insert(secondDegreeFriends[j]);
                    }
                }
            }
        }
        // �ҵ������ͬ���ѵ�3���û� 
        for(set<int>::iterator it=gapFriends.begin();it!=gapFriends.end();++it){
			// �ų��Լ� 
        	if(*it==a){
        		continue;
			}
            vector<int> userFriends = friendships[*it];
            count =index=left=0; 
            // ����������������˫ָ��ȶ� 
            while(index<directFriends.size()&&left<userFriends.size()){
            	if(directFriends[index]<userFriends[left]){
            		++index;
				}
				else if(directFriends[index]>userFriends[left]){
					++left;
				}
				else{
					++index;
					++left;
					++count;
				}
			}
            if(person[0]<count){
            	person[2]=person[1];
            	person[1]=person[0];
            	person[0]=count;
            	answer[2]=answer[1];
            	answer[1]=answer[0];
            	answer[0]=*it;
			}
			else if(person[1]<count){
				person[2]=person[1];
				person[1]=count;
				answer[2]=answer[1];
				answer[1]=*it;
			}
			else if(person[2]<count){
				person[2]=count;
				answer[2]=*it;
			}
        }
        return answer;
    } 
};

// ��ӡ��� 
void printGap(ofstream& file){
    cout<<"############################################"<<endl;
    file<<"############################################"<<endl;
    return;
}

int main() {
	// ��ȡ���� 
	ifstream dataFile("data.txt"); 
	int first,second,num=0,super=0,line=0;
	vector<int> superman(1);
	map<int,int> Super;
    SocialAnalysisNetworkSystem socialNetwork;
    for(int i=0;i<MAX;++i){
    	socialNetwork.addUser(i);
	}
	ofstream outputFile("output.txt");
	// ������ϵ 
	while(dataFile >> first >> second){
		socialNetwork.addFriendship(first, second);
		if(Super[first]){
			++Super[first];
			if(Super[first]>super){
				superman.clear();
				superman.push_back(first);
				super=Super[first];
			}
		}
		else{
			Super[first]=1;
		}
		if(Super[second]){
			++Super[second];
			if(Super[second]>super){
				superman.clear();
				superman.push_back(second);
				super=Super[second];
			}
		}
		else{
			Super[second]=1;
		}
	}
    ifstream sampleFile("sample.txt");
    sampleFile>>num;
    // ��ѯ�û�����������
    for(int i=0;i<num;++i){
    	sampleFile>>first;
    	cout << "�û�"<<first<<"��ֱ����������Ϊ" << socialNetwork.getDirectFriendCount(first)<<"�������������Ϊ"<< socialNetwork.getGapFriend(first)<<"��"<<endl;
    	outputFile << "�û�"<<first<<"��ֱ����������Ϊ" << socialNetwork.getDirectFriendCount(first)<<"�������������Ϊ"<< socialNetwork.getGapFriend(first)<<"��"<<endl;
	}
	printGap(outputFile);
    // ��ѯ�����û�֮�������罻����
    sampleFile>>num;
    for(int i=0;i<num;++i){
    	sampleFile>>first>>second;
        cout << "�û�"<<first<<"���û�" <<second<<"������罻����Ϊ"<<socialNetwork.getShortestDistance(first,second)<<"��" << endl;
        outputFile << "�û�"<<first<<"���û�" <<second<<"������罻����Ϊ"<<socialNetwork.getShortestDistance(first,second)<<"��" << endl;
    }
    printGap(outputFile);
    // ��ѯ�����еġ����������ߡ�
    cout << "�����еġ����������ߡ�Ϊ�û�" << superman[0];
    for(size_t i=1;i<superman.size();++i){
    	cout<<"���û�"<<superman[i];
	}
	cout<<endl;
    outputFile << "�����еġ����������ߡ�Ϊ�û�" << superman[0]<< endl;
    for(size_t i=1;i<superman.size();++i){
    	outputFile<<"���û�"<<superman[i];
	}
	outputFile<<endl;
    printGap(outputFile);
    // ��ѯ�û����Ƽ�����
	sampleFile>>num;
	for(int i=0;i<num;++i){
		sampleFile>>first;
		vector<int> tmp=socialNetwork.recommand(first);
		cout<<"���û�"<<first<<"�Ƽ��û�"<<tmp[0]<<"��"<<tmp[1]<<"��"<<tmp[2]<<"��"<<endl;
		outputFile<<"���û�"<<first<<"�Ƽ��û�"<<tmp[0]<<"��"<<tmp[1]<<"��"<<tmp[2]<<"��"<<endl;
	} 
	printGap(outputFile);
    return 0;
}

/* ������ѵڶ���ʵ��
	int getGapFriend(int userId) {
    	// ֱ������ 
        vector<int> directFriends = friendships[userId];
        // ������� 
        map<int,int> gapFriends;
        int answer=0; 
        // ����ÿ������ 
        for(size_t i=0;i<directFriends.size();++i){
        	gapFriends[directFriends[i]]=1;
        }
        // ����ÿ�����ѵ����� 
        for(size_t i=0;i<directFriends.size();++i){
            vector<int> secondDegreeFriends = friendships[directFriends[i]];
            for(size_t j=0;j<secondDegreeFriends.size();++j){
            	if(!gapFriends[secondDegreeFriends[j]]){
            		gapFriends[secondDegreeFriends[j]]=1;
            		++answer;
				}
			}
        }
        return answer;
    }
*/ 

/* ������ѵ�����ʵ��
	int getGapFriend(int userId) {
		int answer=0;
        for(size_t i=0;i<MAX;++i){
            if(getShortestDistance(userId,i)==2){
            	++answer;
            }
        }
        return answer;
    }
*/ 

