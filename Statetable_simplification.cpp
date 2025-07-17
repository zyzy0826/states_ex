/* Mealy
   Moore 的第二個輸出打0 */
#include <bits/stdc++.h>
using namespace std;

struct state{
    string name;
    string next_state0, next_state1;
    int next_number[2];
    int output[2];
    int group_id = -1;
};

map<string, int> state_id; // 紀錄狀態編號
map<string, int> groups_id; // 紀錄輸出對應的組別
vector<vector<int>> groups; // 全部的組別

int main()
{

    cout << "請輸入狀態數量 : ";
    int state_num; cin >> state_num;

    /* 1. 處理輸入 */

    // 建立狀態表

    vector<state> states;
    cout << "(Moore機第二個輸出寫\'0\')\n";
    cout << "請輸入(空格區分)\n" << "狀態名稱  輸出(0/1)  次態(0/1)\n";

    for(int i = 0; i < state_num; i++){
        state present_state;
        states.push_back(present_state);

        cin >> states[i].name >> states[i].output[0] >> states[i].output[1]
            >> states[i].next_state0 >> states[i].next_state1;
        state_id[states[i].name] = i;
    }

    // 記錄次態編號

    for(state &present_state : states){
        present_state.next_number[0] = state_id[present_state.next_state0];
        present_state.next_number[1] = state_id[present_state.next_state1];
    }

    /* 2. 分組 */

    groups.resize(state_num);

    // 第一次分組依靠輸出狀態來分

    int group_num = 0;
    for(state &present_state : states){
        string st_out;
        st_out += present_state.output[0] + '0';
        st_out += present_state.output[1] + '0';

        int index = groups_id[st_out];
        int stid = state_id[present_state.name];

        if(index == 0){
            groups[group_num++].push_back(stid);
            groups_id[st_out] = group_num;
            present_state.group_id = group_num;
        }else{
            groups[index - 1].push_back(stid);
            present_state.group_id = index;
        }
    }

    /* 3. 循環 */

    while(true){
        vector<vector<int>> new_group;
        new_group.resize(state_num);
        map<string, int> new_gpid;
        int new_gpnum = 0;

        for(int i = 0; i < group_num; i++){ // 對每個組別取各元素
            vector<int> &group = groups[i];

            for(int &s : group){ // 取出陣列中的元素(各組的成員編號)
                state &st = states[s];
                string st_out;
                int ne0 = state_id[ st.next_state0 ];
                int ne1 = state_id[ st.next_state1 ];
                st_out += i + '0';
                st_out += states[ne0].group_id + '0';
                st_out += states[ne1].group_id + '0';

                int index = new_gpid[st_out];
                int stid = state_id[st.name];

                if(index == 0){
                    new_group[new_gpnum++].push_back(stid);
                    new_gpid[st_out] = new_gpnum;
                    // st.group_id = new_gpnum;
                }else{
                    new_group[index - 1].push_back(stid);
                    // st.group_id = index;
                }
            }

        }

        // 是否分完組別?

        if(new_gpnum == group_num)  break; // 組別數不變 == 已分組至最簡

        // 更新組別狀況

        for(int i = 0; i < new_gpnum; i++){
            vector<int> &group = new_group[i];
            for(int s : group){
                states[s].group_id = i+1;
            }
        }

        for(state &st : states){
            st.next_number[0] = new_gpid[st.next_state0];
            st.next_number[1] = new_gpid[st.next_state1];
        }
        groups = new_group;
        group_num = new_gpnum;
        groups_id = new_gpid;
    }

    /* 4. 處理輸出 */

    cout << "\n化簡後: \n" << "狀態名稱  輸出(0/1)  次態(0/1)\n";

    for(int i = 0; i < group_num; i++){
        int j = groups[i][0];

        int next0 = state_id[states[j].next_state0];
        int next1 = state_id[states[j].next_state1];

        string ne0 = states[ groups[ states[next0].group_id - 1 ][0] ].name;
        string ne1 = states[ groups[ states[next1].group_id - 1 ][0] ].name;
        cout << states[j].name << "\t"
             << states[j].output[0] << " " << states[j].output[1] << "\t"
             << ne0 << " " << ne1 << "\n";
    }

}
