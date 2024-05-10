# 🎬 Movie Recommendation System
Author: Ahmad Saadawi
Github: https://github.com/Riasy7/

This README provides a general overview of the Movie Recommendation System. Throughout the program, necessary comments are placed to enhance understanding.

This system is designed to allow users to register, display available movies, rate movies, and receive movie recommendations based on their ratings.
Keep in mind this is a very simple program that is used to showcase a very intersting idea in a simple way. This is also used to showcase how much this can be scaled

Keep note that this code uses text files to keep track of data. This made it very much simple to showcase this concept but of course has room for improvement.

## 📦 Technologies

  - `C Programming Language`

## ✅ Main Function

The main menu is implemented with a while loop:

1. Register User
2. Display Movies
3. Rate a Movie
4. Get Movie Recommendations
5. Exit

The user chooses a number to perform one of the following:

### Register User

Users can register by entering a username. The system checks for existing usernames and prompts for a new one if a match is found. This is handled by the `usernameExists()` function.

### Display Movies

This option lists all available movies by invoking the `displayMovies()` function.

### Rate a Movie

Users can rate movies by entering their username and the movie they wish to rate. This is facilitated by the `checkID()` and `writeToUserRatings()` functions.

### Get Movie Recommendations

Based on previous ratings, the system provides movie recommendations using the `movieRecommendation()` function.

## 📈 Data Structure

This part is really simple, I did not want to make it complicated and just used text files.
So, user data and movie ratings are stored in text files, structured for easy access and manipulation. Each user and movie is represented in a structured format to maintain clarity and consistency.
This could be majorily improved.

## Functions

A brief description of key functions:

- `usernameExists(char* userName, int* userID)`: Checks for an existing username.
- `addUserToFile(char* userName, int* userID)`: Registers a new user.
- `displayMovies()`: Displays a list of available movies.
- `checkID(char* userName)`: Retrieves the ID associated with a username.
- `writeToUserRatings(int movieNumber, int movieRating, int userID)`: Logs a user's movie rating.
- `movieRecommendation(char* userName)`: Generates movie recommendations based on user ratings.

### 🤔🔑 Improvements

Here are potential improvements to consider for scaling or refining the application:

    1. **Struct Implementation**: Use structs for organized data management of movies and users.
    2. **Function Separation**: Modularize the code into separate functions for each major feature for better maintainability.
    3. **Error Handling**: Improve file operation robustness by handling potential read/write errors more effectively.
    4. **Global Variables**: Minimize the use of global variables to avoid potential conflicts and enhance code reliability.
    5. **Code Readability**: This code is all in one file. I find that this is very ugly and is the major downside. If this was a large application, to improve it, scalability of the file would be needed. This means that having multiple files and modules for each responsible function and having header files would greatly help.

This guide is also part of me learning to improve my C programming.
A lot of the aspects like code readability and organization I am not too happy about and could use major major major improvements.

Now what can those major improvements be if we wanted to scale to a large applciation;

### 🚀 Scaling to a Large Online Application

As we envision this system handling thousands of concurrent users and a significant database of movies and ratings, there are key architectural and technological shifts required to ensure scalability, reliability, and maintainability:

    1. **Database Integration**: Transition from using text files to a robust database system like PostgreSQL or MongoDB. This would allow for efficient data management, and scalabiilty. Implementing a database would obviously also facilitate better data integrity then simple text files lol.
    2. **Microservices Architecture**: Decompose the application into microservices to improve scalability and maintainability. This allows each part of the system (ex: user registration, movie displaying, rating processing, recommendation generation) to scale independently.
    3. **User Authentication and Security**: Implement secure authentication mechanisms like OAuth or JWT for user management. This ensures that user data and actions are secured, especially in an environment where personal and sensitive data are handled.
    4. **API Development**: Develop a RESTful API to handle requests between the client-side and server-side. This would allow for a more modular frontend that can be developed independently of the backend and can be scaled easily.
    5. **Caching Mechanisms**: Integrate caching strategies using tools like Redis to store frequently accessed data such as movie lists and top recommendations. This reduces the load on the database and speeds up response times for end users.
    6. **Performance Monitoring and Logging**: Incorporate comprehensive monitoring and logging systems to track the performance of the application and to quickly identify and troubleshoot issues. Tools like Prometheus for monitoring and ELK Stack for logging can be utilized.
    7. **Continuous Integration and Deployment (CI/CD)**: Implement CI/CD pipelines to automate testing and deployment processes. This ensures that new code changes can be rapidly and safely deployed to production without downtime.
    8. **User Interface and Experience**: Design a responsive and intuitive user interface that can handle various devices and screen sizes. Employing frameworks like React or Vue.js for the frontend can enhance the user experience with dynamic updates and interactive elements.

By actually taking the time to look at those areas this small idea could be turned into a big scalable robust online application/platform.
Again, this is why I like to simplify my code and reflect on it so I can learn even more.

## Thank you for your time 🙂
