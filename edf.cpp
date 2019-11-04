    #include<bits/stdc++.h>
    using namespace std;

     struct Task {
     int phase,releaseTime, extime, period, deadline;
    };

    struct Job {
     int i, j, releaseTime, extime, deadline;
    };
    struct compareDeadline {
        bool operator()(Job &a , Job &b){
           if (a.deadline==b.deadline){
            return a.releaseTime>b.releaseTime;
           } else return a.deadline>b.deadline;
        }
    };



    int main(){



        freopen("input.txt", "r", stdin);
        int noOfTasks;
        Task tasks[100];
        Job tempJob;
        map<int, vector<Job> > jobReleasedAt;
        priority_queue< Job  , vector< Job >, compareDeadline  > jobs;
        cout<<"Enter the no of tasks"<<endl;
        cin>>noOfTasks;
        int MAXTIME = 20;
        cout<<"Enter phase, extime, period and deadline of each task"<<endl;
        for (int i=1;i<=noOfTasks;i++){
           cin>>tasks[i].phase>>tasks[i].extime>>tasks[i].period>>tasks[i].deadline;

           for (int j=1;(j-1)*tasks[i].period<MAXTIME; j++){ // j denotes the job no of corr. task
                  tempJob.i = i;
                  tempJob.j = j;
                  tempJob.releaseTime = tasks[i].phase + (j-1)*tasks[i].period;
                  tempJob.extime = tasks[i].extime;
                  tempJob.deadline = tempJob.releaseTime + tasks[i].deadline;
                  //jobs.push(tempJob);
                  // storing job released at corr. time
                  jobReleasedAt[tempJob.releaseTime].push_back(tempJob);
           }
        }


        Job currentJob;
        currentJob.extime= 0;
        for (int t=0;t<=MAXTIME;t++){

               for (int i=0;i<jobReleasedAt[t].size();i++){
                 jobs.push(jobReleasedAt[t][i]);
               }
               // check if the job to be executed has zero execution time left
                if (currentJob.extime<=0){
                        if (t>0)cout<<"job ("<<currentJob.i<<","<<currentJob.j<<") completed at time:"<<t<<endl;
                     // check if there is any job in the job queue
                       if (!jobs.empty()){
                        currentJob = jobs.top();
                        jobs.pop();
                        cout<<"job ("<<currentJob.i<<","<<currentJob.j<<") started at time:"<<t<<endl;
                       } else cout<<"cpu idle at time:" << t<<endl;
                } else {
                    // check if any job has arrived just at this time
                      if (jobReleasedAt[t].size()>0){
                         if (currentJob.deadline>jobs.top().deadline){
                            jobs.push(currentJob);
                            cout<<"job ("<<currentJob.i<<","<<currentJob.j<<") preempted at time:"<<t<<endl;
                            currentJob = jobs.top();
                            cout<<"job ("<<currentJob.i<<","<<currentJob.j<<") started at time:"<<t<<endl;
                            jobs.pop();
                         }
                      }



                }

               // at this second one unit of the job will be executed
               if(currentJob.extime + t>currentJob.deadline){
                cout<<"SCHEDULE INFEASIBLE JOB ("<<currentJob.i<<","<<currentJob.j<<") missed the deadline"<<endl;
                break;
               } else currentJob.extime--;
              }
    return 0;
    }


