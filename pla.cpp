#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int act_func(float z)
{
    return ((z>0) ? 1 : -1 );
}

int main()
{
    ifstream data;
    char buffer[256] = {0};
    float temp;
    vector < vector<float> > data_vec;
    
    data.open("data.txt");

    if(!data.is_open())
        cout<<"failed";
    else
    {
        while(!data.eof())
        {
            vector<float> data_row;
            data.getline(buffer,sizeof(buffer));
            istringstream in(buffer);
            while(in>>temp)
            {
                data_row.emplace_back(temp);
            }
            data_vec.emplace_back(data_row);
        }
        data.close();

        // for(auto i : data_vec)
        // {
        //     for(auto j : i)
        //     {
        //         cout << j <<" ";
        //     }
                
        //     cout << "\n";
        // }
    }

    vector <float> w(data_vec[0].size()-1,0);
    float dot=0;
    int update=0;
    int flag=1;

    while(flag!=0)
    {
        flag=0;
        for (int i=0;i<data_vec.size();++i)
            {
                dot=0;
                for(int j=0;j<data_vec[i].size()-1;++j)
                {
                    dot+=data_vec[i][j]*w[j];
                }
                if(act_func(dot)!=data_vec[ i ][ data_vec[i].size()-1 ])            //activate_fx(w*x)!=y
                {
                    update++;
                    flag+=1;
                    for(int j=0;j<data_vec[i].size()-1;++j)
                    {
                        w[j]+=data_vec[ i ][ data_vec[i].size()-1 ]*data_vec[i][j]; //w += y*x
                    }
                }
            }
    }

    cout<<"w:";
    for(int i=0;i<w.size();++i)
        cout<<w[i]<<" ";

    cout<<"\nnumber of updates: "<<update;

    //w:-3 3.08414 -1.58308 2.3913 4.52876
    //number of updates: 45
    
    return 0;
}