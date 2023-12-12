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
	// 存储朋友关系 
   	map< int , vector <int> > friendships;
public:
    // 添加用户
    void addUser(int userId) {
        friendships[userId] = {};
    }

    // 添加朋友关系
    void addFriendship(int user_a, int user_b) {
        friendships[user_a].push_back(user_b);
        friendships[user_b].push_back(user_a);
    }

    // 查询用户的直接朋友数量
    int getDirectFriendCount(int userId) {
        return friendships[userId].size();
    }
    
    // 查询用户的间接朋友数量 
    int getGapFriend(int userId) {
    	// 直接朋友 
        vector<int> directFriends = friendships[userId];
        // 间接朋友 
        set<int> gapFriends;
        // 遍历每个朋友 
        for(size_t i=0;i<directFriends.size();++i){
        	// 朋友的朋友 
            vector<int> secondDegreeFriends = friendships[directFriends[i]];
            for(size_t j=0;j<secondDegreeFriends.size();++j){
				for (size_t k = 0; k < directFriends.size(); ++k) {
					// 确保不是用户的朋友 
    				if (directFriends[k] == secondDegreeFriends[j]) {
        				break;
    				}
    				// 确定是用户朋友的朋友 
    				if (k == directFriends.size() - 1) {
        				gapFriends.insert(secondDegreeFriends[j]);
    				}
				}
			}
        }
        // 排除用户自己 
        return gapFriends.size()-1;
    }

    // 计算两个用户之间的最短社交距离
    int getShortestDistance(int startUserId, int targetUserId) {
        // 自己和自己的距离为0 
		if (startUserId == targetUserId) {
            return 0;
        }
        // 记录已有朋友关系 
        map<int, bool> visited;
        // 暂存新一层朋友关系 
        queue<pair<int, int> > q;
        q.push({startUserId, 0});
        visited[startUserId] = true;
        while (!q.empty()) {
            pair<int,int> current = q.front();
            q.pop();
            for(size_t i=0;i<friendships[current.first].size();++i){
            	// 找到 
                if (friendships[current.first][i]== targetUserId) {
                    return current.second + 1;
                }
                // 没找到，存入下一层 
                if (!visited[friendships[current.first][i]]) {
                    q.push({friendships[current.first][i], current.second + 1});
                    visited[friendships[current.first][i]] = true;
                }
            }
        }
        return INT_MAX;
    }
    
    // 查询共同好友最多的3个用户
	vector<int> recommand(int a) {
        vector<int> directFriends = friendships[a],answer(3,-1),person(3,-1);
        set<int> gapFriends;
        int count;
        size_t index,left;
        // 找到和用户a距离大于1的所有用户
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
        // 找到最多相同好友的3个用户 
        for(set<int>::iterator it=gapFriends.begin();it!=gapFriends.end();++it){
			// 排除自己 
        	if(*it==a){
        		continue;
			}
            vector<int> userFriends = friendships[*it];
            count =index=left=0; 
            // 利用数据有序性用双指针比对 
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

// 打印间隔 
void printGap(ofstream& file){
    cout<<"############################################"<<endl;
    file<<"############################################"<<endl;
    return;
}

int main() {
	// 读取数据 
	ifstream dataFile("data.txt"); 
	int first,second,num=0,super=0,line=0;
	vector<int> superman(1);
	map<int,int> Super;
    SocialAnalysisNetworkSystem socialNetwork;
    for(int i=0;i<MAX;++i){
    	socialNetwork.addUser(i);
	}
	ofstream outputFile("output.txt");
	// 构建关系 
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
    // 查询用户的朋友数量
    for(int i=0;i<num;++i){
    	sampleFile>>first;
    	cout << "用户"<<first<<"的直接朋友数量为" << socialNetwork.getDirectFriendCount(first)<<"，间接朋友数量为"<< socialNetwork.getGapFriend(first)<<"。"<<endl;
    	outputFile << "用户"<<first<<"的直接朋友数量为" << socialNetwork.getDirectFriendCount(first)<<"，间接朋友数量为"<< socialNetwork.getGapFriend(first)<<"。"<<endl;
	}
	printGap(outputFile);
    // 查询两个用户之间的最短社交距离
    sampleFile>>num;
    for(int i=0;i<num;++i){
    	sampleFile>>first>>second;
        cout << "用户"<<first<<"和用户" <<second<<"的最短社交距离为"<<socialNetwork.getShortestDistance(first,second)<<"。" << endl;
        outputFile << "用户"<<first<<"和用户" <<second<<"的最短社交距离为"<<socialNetwork.getShortestDistance(first,second)<<"。" << endl;
    }
    printGap(outputFile);
    // 查询网络中的“超级连接者”
    cout << "网络中的“超级连接者”为用户" << superman[0];
    for(size_t i=1;i<superman.size();++i){
    	cout<<"和用户"<<superman[i];
	}
	cout<<endl;
    outputFile << "网络中的“超级连接者”为用户" << superman[0]<< endl;
    for(size_t i=1;i<superman.size();++i){
    	outputFile<<"和用户"<<superman[i];
	}
	outputFile<<endl;
    printGap(outputFile);
    // 查询用户的推荐朋友
	sampleFile>>num;
	for(int i=0;i<num;++i){
		sampleFile>>first;
		vector<int> tmp=socialNetwork.recommand(first);
		cout<<"向用户"<<first<<"推荐用户"<<tmp[0]<<"，"<<tmp[1]<<"，"<<tmp[2]<<"。"<<endl;
		outputFile<<"向用户"<<first<<"推荐用户"<<tmp[0]<<"，"<<tmp[1]<<"，"<<tmp[2]<<"。"<<endl;
	} 
	printGap(outputFile);
    return 0;
}

/* 间接朋友第二种实现
	int getGapFriend(int userId) {
    	// 直接朋友 
        vector<int> directFriends = friendships[userId];
        // 间接朋友 
        map<int,int> gapFriends;
        int answer=0; 
        // 遍历每个朋友 
        for(size_t i=0;i<directFriends.size();++i){
        	gapFriends[directFriends[i]]=1;
        }
        // 遍历每个朋友的朋友 
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

/* 间接朋友第三种实现
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

