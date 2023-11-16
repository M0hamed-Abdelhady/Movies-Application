# Movies Application
Movies Application is a C++ console application, leveraging the Model-View-Controller (MVC) pattern.

## Features:
- **Signup**:
   - Sign up as a user.
- **Login**:
   -  Secure login and authentication processes.
   - Remember the user for 30 days (without logout).
- **Roles**:
   - **Admins**:
      - Managing Admin: The admin can delete another admin if and only if it was an older admin.
      - Managing Users:
         - Viewing the user's account information.
         - Add a new user.
         - Delete a user.
         - designate a user as admin.
      - Managing Movies:
         - Viewing the movie's details.
         - Add a new movie.
         - Delete a movie.
      - Viewing system watch history.
      - Viewing their own account information.
   - **Users**:
      - Browsing available movies.
      - Viewing a time-sorted watch history and removing watch records.
      - Managing the list of user's favorite movies.
      - Viewing their account information
      - Delete account.

## Databsae
Movies App is a file-based database console application, featuring distinct files for different data entities. This file-based database architecture included:
- `Admins`: Contains admins' accounts and their relevant data.
- `Users`: Contains users' accounts and their relevant data.
- `Movies`: Contains movie data.
- `Records`: Maintaining a comprehensive watch history, recording user ID, movie ID, and timestamp, establishing a one-to-many relationship with the user and the movie.
- `Favorite`: Maintained a comprehensive Favorite list, recording user ID, movie ID, and timestamp, establishing a one-to-many relationship with the user and the movie.
- `SystemLogs`: Managed user login history, facilitating automatic login within 30 days after the app's exit without explicit logout.


## Prerequisites
- C++ compiler(e.g., GNU)

## How to use
1. Clone the repository(must install git) or download the ZIP file:
   ```bash
   git clone https://github.com/M0hamed-Abdelhady/Movies-Application
2. Compile the code (or simply run Movies Application.exe) :
     ```bash
     g++ -o Movies_Application main.cpp
3. Run the application:
   ```bash
   ./Movies_Application

## Customization

## License
This project is licensed under the [MIT License](https://opensource.org/license/mit/).
