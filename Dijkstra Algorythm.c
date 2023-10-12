#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>


//The node will have an identifier(to know which node are we talking about), a cost and an array with the path.
struct node{
    int identif;
    int cost;
    int path[8];
};
struct node info [8]; //In this array I will store the nodes that are aAAdjacent to the ones I have visited.
int visitados[8];   //In this array I will store the nodes I have already visited.

int main(){
    FILE* given;    //File in which I have the matrix of costs.
    char content[1000];
    int i = 0;
    int j = 0;
    int costs_matrix[8][8];
    char delim[] = " ";
    

    int num_visitados = 0;  //This variable stores the number of visited nodes.
    
    int num_path = 0;
    
    int min_cost_owner =100;    //This variable is used to know which is the node that has the smaller cost in the struct node info[].
    int current;    //Tells which node is the one we are currently at. So that we can know its adjacent nodes(with their respective costs).
    int dest;   //Here I will store the destination node that the user chooses.
    int flag_dot = 0;   //This flag will be raised when the last node of the path has been printed on screen, so that a "." is printed.
    


    given = fopen("costs.txt","r"); //I open the file where I have the costs in a matrix.
    //Now I will read line by line in the file and taking the information separated by spaces (that's why delim[]=" ";).
    //Once I obtain that information, i will store it in "costs_matrix[8][8]";
    while(fgets(content,1000,given)!= NULL){  
        int cost = atoi(strtok(content,delim));
        j = 0;
        while (j<=7){
            costs_matrix[i][j] = cost;
            cost = atoi(strtok(NULL,delim));
            j++;
        }
        i++;
    }
    //Now I print the menu in which I ask the user for the source node.
    printf("Please introduce the source point: \n");
    printf("For A, introduce 0\n");
    printf("For B, introduce 1\n");
    printf("For C, introduce 2\n");
    printf("For D, introduce 3\n");
    printf("For E, introduce 4\n");
    printf("For F, introduce 5\n");
    printf("For G, introduce 6\n");
    printf("For H, introduce 7\n");
    printf("Source point:");
    scanf("%d",&current);

    //In the info array, I set the cost of the source to zero.
    info [current].cost = 0;
    info [current].path[0] = current;   //And I set itself as the start of the path to itself.
    //Now, I set the rest of the path array to -1 (as none of the nodes is negative, it will be an easy way to know when the path ends at the end of the program).
    for(int g = 1;g<8;g++){
        if(g != current){
            info [current].path[g] = -1;
        }
    }
    //As I have still not studied the adjacent nodes, I set them to infinity (500).
    for(int i =0;i<8;i++){
        if(i!= current){
            info [i].cost = 500;
        }
    }
    
    //The loop will run until I have visited all the 8 nodes.
    while(num_visitados<8){
        //I add the source node to visitados array.
        visitados[num_visitados] = current;
        //I update the number of visited nodes.
        num_visitados++;
        
        
        for(int a = 0; a<8; a++){   //I will go through the costs matrix to check the cost to the adjacent nodes
            int visited_flag = 0;   //I update "visited_flag" to zero as I will need to check whether the nodes have been visited or not and 
                                    //in the previous loop, it could have been changed if a visited node has been found, so I reset it.
            int flag = 0;   //Flag used while updating the path to a node. It will be used to copy the adjacent node to the path when the first
                            //-1 is detected.
            for(int e = 0; e < num_visitados; e++){ //I will go at the same time through the visited nodes to check if the adjacent nodes
                                                    //to the current one have been visited or not. If they have been visited, i no longer care
                                                    //about them as I don´t need to go back to them.
                if(visitados[e]== a){   //If the node on the visited array matches the adjacent node to the current one, then we rise the flag.
                    visited_flag = 1;
                }
            }
            if((costs_matrix[current][a] < 200) && (costs_matrix[current][a] > 0) && (visited_flag == 0)){  //I will enter here if I find a cost
                                                                                                            //that is greater than zero (if it is
                                                                                                            //zero it means it is itself), and
                                                                                                            //the cost is smaller than infinity
                                                                                                            //and the visited_flag has not been
                                                                                                            //risen, meaning the adjacent node
                                                                                                            //has not been visited.
                if(info [a].cost >= costs_matrix[current][a] + info[current].cost){ //If the previous cost assigned to that node is greater than
                                                                                    //the cost through the path that we are traversing right now,
                                                                                    //it means that the new path is cheaper.
                    info [a].cost = costs_matrix[current][a] + info[current].cost;  //Updating the cost for the new path (cheaper one).
                    for(int b = 0; b< 8; b++){  //Updating the path.
                    if(flag == 0 && info [current].path[b] == -1 ){ //If a -1 is detected and the flag is not rised, then I have to add the node
                                                                    //to the path and rise the flag so that then it keeps copying the path. 
                        info [a].path[b] = a;
                        flag = 1;
                    }
                    else{
                        info [a].path[b] = info [current].path[b];
                    }
                }
                }
                
            }
        }


        int min_cost = 500; //Rest the minimum cost to a very high value.

        for(int d = 0; d<8;d++){
            //I will go through the visited nodes array to check if the current node has already been visited or not. If so, I will rise "visited_flag"
            int visited_flag = 0;
            for(int e = 0; e < num_visitados; e++){
                if(visitados[e]== d){
                    visited_flag = 1;
                }
            }
            //If current node has not been already visited, meaning "visited_flag" has not been risen, I will enter the if.
            if(visited_flag == 0){
                if((info [d].cost < min_cost)){ //I will check if the cost is smaller than what has been considered smaller until now.
                                                //If it is smaller, then that cost is the smallest cost (by the time). I will also note down
                                                //which is the node that has that smallest cost.
                    min_cost = info [d].cost;
                    min_cost_owner = d;
                }
            }
        }
            

        current = min_cost_owner;
    }
    //Now I print the menu in which I ask the user for the destination node.
    printf("*****************************************************\n");
    printf("Please introduce the destination point: \n");
    printf("For A, introduce 0\n");
    printf("For B, introduce 1\n");
    printf("For C, introduce 2\n");
    printf("For D, introduce 3\n");
    printf("For E, introduce 4\n");
    printf("For F, introduce 5\n");
    printf("For G, introduce 6\n");
    printf("For H, introduce 7\n");
    printf("Source point:");
    scanf("%d",&dest);

    for(int f = 0; f<8;f++){
        //If the flag_dot is 1, it means that the first -1 has been detected, meaning that the final node of the path (destination node) has been already printed
        //Once that happens, the remaining numbers of the "info [dest].path[]" array don´t need to be printed as all of them will be -1's.
        if(flag_dot == 1){

        }else{
            //I will enter here when there are still possible nodes of the path left to print.
            if(info [dest].path[f] != -1){  //If the current number on "info [dest].path[]" is NOT a -1, it means the destination node has NOT 
                                            //been printed and I need to print anything more, so I print one more.
                printf("%d",info [dest].path[f]);
            }
            if(info [dest].path[f+1] != -1){    //If the following number of the array is NOT  a "-1", then it means that there are still nodes
                                                //left to print, so I print a ",".
                printf(", ");
            }else{  //If the current number on "info [dest].path[]" is a -1, it means the destination node has been printed 
                    //and I don´t need to print anything else, so I turn "flag_dot" to 1 and I print a "."
                printf(".\n");
                flag_dot = 1;
            }
        }

        
    }
    //Now I print the cost of the final path.
    printf("User, the cost is: %d.\n",info [dest].cost);
}