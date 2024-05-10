/**
Movie Recommendation System
--------------------------
Author: Ahmad Saadawi
GitHub: github.com/Riasy7
--------------------------
Description:
This simple program is a movie recommendation system that allows users to register, rate movies, and get movie recommendations based on their ratings.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_USERS 100
#define NUM_MOVIES 10


// this method checks if the username exists in the user_data file
int usernameExists(char *username, int *userID) { // here this function expects a pointer to a function

	char line[100];
	FILE *userData = fopen("/root/comp348/user_data.txt", "r"); // open file for read only

	if (userData == NULL) {
		printf("Error opening file."); // handling file opening error
        exit(1);
	}

	*userID = 1; // start user id at 1 because there is no 0th user

	while(fgets(line, sizeof(line), userData)) { // while loop to read till EOF

		char *token = strtok(line, " "); // strtok method to check first "toklen" found in line, returns pointer to that name
		if (token != NULL) {
			(*userID)++; // increment user id for each existing user in the file
		}
		if (token != NULL && strcasecmp(token, username) == 0) { // logic for username already exists

			fclose(userData);
			return 1;
		}
	}
	fclose(userData);
	return 0; // username does not exist

}

// this method adds a user to the user_data file
void addUserToFile(char *username, int *userID) {

	FILE *userData = fopen("/root/comp348/user_data.txt", "a"); // open file for appending

	if (userData == NULL) {
		printf("Error opening file."); // handling file opening error
        exit(1);
        }

	char line[100];

	while(fgets(line, sizeof(line), userData)) { // keeping track of user id's by using a while loop and checking if theres a username on each line

		char *token = strtok(line, " ");
		if (token != NULL) {
			(userID)++; // the () makes it so that its incremented at where its pointed at so the variable at main
		}
	}

	fprintf(userData, "%s %d\n", username, *userID); // write to userData file
	fclose(userData);
}

// this method replaces underscores with spaces
// simple string manipulation
void replaceUnderscoreWithSpace(char *str) { 
    for(int i = 0; str[i]; i++){
        if(str[i] == '_'){
            str[i] = ' ';
        }
    }
}

// this method displays the movies from the movie_database file
void displayMovies() {
    FILE *movieDatabase = fopen("/root/comp348/movie_database.txt", "r");
    if (movieDatabase == NULL) {
        printf("Error opening file."); // handling file opening error
        exit(1);
    }
    char title[50], genre[20];
    float rating;
    int counter = 1; // counter to keep track of the number of movies and then display them, no 0th movie
    printf("Displaying Movies\n");
    while(fscanf(movieDatabase, "%s %s %f", title, genre, &rating) != EOF) { // while loop to read till EOF and to keep track of genre and rating for display purposes
        replaceUnderscoreWithSpace(title);
        printf("%d. %s (%s) - %.1f\n", counter, title, genre, rating); 
        counter++;
    }   
    fclose(movieDatabase);
}

// this method checks the user id of the user that is inputed and returns the user id
// this is for case 3 where the user needs to rate a movies
int checkID(char *username) {
    FILE *userData = fopen("/root/comp348/user_data.txt", "r");
    if (userData == NULL) {
        printf("Error opening file."); // handling file opening error
        return -1;
    }
    char line[100];
    int userID = 1; // start the user ID at 1
    while(fgets(line, sizeof(line), userData)) {
        char *token = strtok(line, " ");
        if (token != NULL && strcasecmp(token, username) == 0) {
            fclose(userData);
            return userID; // return the current line number as the user ID
        }
        userID++;
    }
    fclose(userData);
    return -1; // it will return -1 if the user was not found
}

// this method writes to the user_ratings file while updating the ratings
// it will keep into account the number of users and movies and update the ratings properly
void writeToUserRatings(int movieNumber, int movieRating, int userID) {
    FILE *userRatings = fopen("/root/comp348/user_ratings.txt", "r+");
    if (userRatings == NULL) {
        printf("Error opening file."); // handling file opening error
        exit(1);
    }

    int numUsers, numMovies;
    fscanf(userRatings, "%d %d", &numUsers, &numMovies); // read the number of users and movies from the first line of the file

    float ratings[MAX_USERS][NUM_MOVIES]; // 2D array to store the ratings for each user and movie
    for (int i = 0; i < numUsers; i++) {
        for (int j = 0; j < numMovies; j++) {
            fscanf(userRatings, "%f", &ratings[i][j]);
        }
    }

    if (userID > numUsers) {
        numUsers = userID; // update the number of users if the user ID is greater than the current number of users
        for (int i = numUsers; i < userID; i++) {
            for (int j = 0; j < NUM_MOVIES; j++) {
                ratings[i][j] = 0.0; // initialize the new rows to 0.0 since the user hasn't rated any movies yet
            }
        }
    }

    
    ratings[userID - 1][movieNumber - 1] = movieRating; // update the rating for the specified user and movie

    rewind(userRatings); // update the number of users and movies at the beginning of the file
    fprintf(userRatings, "%d %d\n", numUsers, numMovies); // write the updated number of users and movies
    for (int i = 0; i < numUsers; i++) {
        for (int j = 0; j < numMovies; j++) {
            fprintf(userRatings, "%.1f ", ratings[i][j]); // write each rating
        }
        fprintf(userRatings, "\n");
    }

    fclose(userRatings);
}

// this method will recommend movies to the user based on the ratings
// the algorithmn used will calculate the average rating for each movie and then recommend the highest rated movies
// if the user has not rated the movie yet, it will recommend it
// if the user has rated the movie, it will not recommend it
// it will also check if the user exists
void movieRecommendation(char *username) {
    FILE *userRatings = fopen("/root/comp348/user_ratings.txt", "r");
    if (userRatings == NULL) {
        printf("Error opening file."); // handling file opening error
        exit(1);
    }
    int numUsers, numMovies; // read the number of users and movies from the first line of the file
    fscanf(userRatings, "%d %d", &numUsers, &numMovies);

    float ratings[MAX_USERS][NUM_MOVIES]; // 2D array to store the ratings for each user and movie
    for (int i = 0; i < numUsers; i++) {
        for (int j = 0; j < numMovies; j++) {
            fscanf(userRatings, "%f", &ratings[i][j]);
        }
    }
    fclose(userRatings);

    int userID = checkID(username); // using other method to check if the user exists
    if (userID == -1) {
        printf("User not found. Please register first.\n");
        return;
    }

    float averageRatings[NUM_MOVIES] = {0}; // calculate the average rating for each movie
    int ratingCounts[NUM_MOVIES] = {0};
    for (int i = 0; i < numUsers; i++) {
        for (int j = 0; j < numMovies; j++) {
            if (ratings[i][j] != 0.0) { // only count non-zero ratings
                averageRatings[j] += ratings[i][j];
                ratingCounts[j]++;
            }
        }
    }

    for (int i = 0; i < numMovies; i++) {
        if (ratingCounts[i] != 0) {
            averageRatings[i] /= ratingCounts[i];
        }
    }

    FILE *movieDatabase = fopen("/root/comp348/movie_database.txt", "r"); // print the movies with the highest average ratings that the user hasn't rated yet
    if (movieDatabase == NULL) {
        printf("Error opening file."); // handling file opening error
        exit(1);
    }

    char title[50], genre[20];
    float rating;
    int counter = 1;
    printf("Recommended Movies for %s:\n", username);
    while(fscanf(movieDatabase, "%s %s %f", title, genre, &rating) != EOF) {
        if (ratings[userID - 1][counter - 1] == 0.0) { // the user hasn't rated this movie yet
            replaceUnderscoreWithSpace(title); // use my method to replace underscores with spaces
            printf("%d. %s (%s) - %.1f\n", counter, title, genre, averageRatings[counter - 1]);
        }
        counter++;
    }

    fclose(movieDatabase);
}

int main() {

	int input = -1;  // store user input
	int userID = 1;  

	while (input != 0) { // main while loop to keep the menu running
		printf("***** Movie Recommendation System *****\n"
			"1. Register User\n"
			"2. Display Movies\n"
			"3. Rate a Movie\n"
			"4. Get Movie Recommendations\n"
			"0. Exit\n"
			"Enter your choice: ");

		scanf("%d", &input);

		
		if (input == 1) { // case 1: Register User

			char userName[100];
			int userExists;

			do { // do while loop to keep checking if username exists, if it doesnt it'll break out

				printf("Please enter your name:\n");
				scanf("%s", userName);

				userExists = usernameExists(userName, &userID);

				if(userExists) {
					printf("User already exists. Please choose a different name.\n");
				}

			} while (userExists);

			addUserToFile(userName, &userID); // write to file
			printf("User %s is successfully registered!\n", userName);
		}

		if (input == 2) { // Case 2: Display Movies
			displayMovies();
		}

		if (input == 3) { // Case 3: Rate a Movie
			char userName[100];
			int userExists;
			int userID;
			printf("Please enter your username:\n");
			scanf("%s", userName);

			userExists = usernameExists(userName, &userID);
			if (userExists == 0) {
				printf("User does not exist. Please Register First\n");
				continue;
			}
			else {

				userID = checkID(userName);
				displayMovies();
				int movieNumber, movieRating;
				while (1) {
					printf("Enter the movie number you want to rate: ");
					scanf("%d", &movieNumber);
					if (movieNumber < 1 || movieNumber > 10) {
						printf("Invalid movie number. Please enter a number between 1 and 10.\n");
					}
					else {
                        break;
                    }
				}
				
				while (1) {
					printf("Enter the rating for the movie (1-5): ");
					scanf("%d", &movieRating);
					if (movieRating < 1 || movieRating > 5) {
						printf("Invalid rating. Please enter a rating between 1 and 5.\n");
					}
                    else {
                        break;
                    }
					
				}
				writeToUserRatings(movieNumber, movieRating, userID);
				printf("Rating has been successfully recorded!\n");
			}
		}

		if (input == 4) { // Case 4: Get Movie Recommendations
			char userName[100];
			int userExists;
			int userID;
			printf("Please enter your username:\n");
			scanf("%s", userName);

			userExists = usernameExists(userName, &userID);
			if (userExists == 0) {
				printf("User does not exist. Please Register First\n");
				continue;
			}
			else {
				movieRecommendation(userName);
			}

		}
	}
	return 0;
}




