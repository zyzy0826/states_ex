/* Mealy
   Moore ���ĤG�ӿ�X��0 */
#include <bits/stdc++.h>
using namespace std;

struct state{
    string name;
    string next_state0, next_state1;
    int next_number[2];
    int output[2];
    int group_id = -1;
};

map<string, int> state_id; // �������A�s��
map<string, int> groups_id; // ������X�������էO
vector<vector<int>> groups; // �������էO

int main()
{

    cout << "�п�J���A�ƶq : ";
    int state_num; cin >> state_num;

    /* 1. �B�z��J */

    // �إߪ��A��

    vector<state> states;
    cout << "(Moore���ĤG�ӿ�X�g\'0\')\n";
    cout << "�п�J(�Ů�Ϥ�)\n" << "���A�W��  ��X(0/1)  ���A(0/1)\n";

    for(int i = 0; i < state_num; i++){
        state present_state;
        states.push_back(present_state);

        cin >> states[i].name >> states[i].output[0] >> states[i].output[1]
            >> states[i].next_state0 >> states[i].next_state1;
        state_id[states[i].name] = i;
    }

    // �O�����A�s��

    for(state &present_state : states){
        present_state.next_number[0] = state_id[present_state.next_state0];
        present_state.next_number[1] = state_id[present_state.next_state1];
    }

    /* 2. ���� */

    groups.resize(state_num);

    // �Ĥ@�����ը̾a��X���A�Ӥ�

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

    /* 3. �`�� */

    while(true){
        vector<vector<int>> new_group;
        new_group.resize(state_num);
        map<string, int> new_gpid;
        int new_gpnum = 0;

        for(int i = 0; i < group_num; i++){ // ��C�ӲէO���U����
            vector<int> &group = groups[i];

            for(int &s : group){ // ���X�}�C��������(�U�ժ������s��)
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

        // �O�_�����էO?

        if(new_gpnum == group_num)  break; // �էO�Ƥ��� == �w���զܳ�²

        // ��s�էO���p

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

    // output

    cout << "\n��²��: \n" << "���A�W��  ��X(0/1)  ���A(0/1)\n";

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


/*

�o�O�ڷQ���g���{���@�Ǩ��骺��B�Q�k

*���A���²�X�X���ժk
1. �ھ�input����X���A����
2. �ھڦPgroup���U���A�����A�O�_�b�P��
���P�աG�d�� / ���P�G��ա]���A�b�P�ժ̤���P�@�ա^
3. ���ưʧ@2����L�k�A����
4. �դ�sort�]�r��Ǥp�̱ƫe�^
5. �X�֡A���A��u�d�U�U�ձ��Y�A�P�ժ̥ѱ��Y���N

�D�J���D
1. ���աG�̦h�|��(2^2)

*/

/*
A 0 0 C F
B 0 1 E F
C 0 0 B C
D 0 1 C F
E 0 0 D E
F 0 0 A E

A 0 0 C B
B 1 0 A E
C 0 0 D F
D 0 0 A B
E 1 0 B D
F 1 0 C E

A 0 0 C D
B 1 0 E A
C 0 0 A E
D 1 0 D F
E 1 0 B C
F 0 0 A B

S0 0 0 S1 S4
S1 0 1 S0 S4
S2 0 1 S3 S2
S3 1 0 S5 S4
S4 1 0 S0 S3
S5 0 0 S2 S3
*/
