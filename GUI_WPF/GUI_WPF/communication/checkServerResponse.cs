using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;


namespace GUI_WPF
{
    public class checkServerResponse
    {
        public const char ERROR_RESPONSE = 'c';
        public const int MAX_DATA_SIZE = 4;
        public enum Status { STATUS_USER_DOESNT_EXIST = 1, STATUS_USER_EXIST, STATUS_PASSWORD_DOESNT_MATCH, STATUS_SUCCESS, STATUS_ALREADY_LOGGED_IN, STATUS_DOESNT_LOGGED_IN, STATUS_NO_ROOMS, STATUS_NO_USERS_LOGGED_IN, STATUS_ROOM_DOESNT_EXIST, STATUS_DB_PROBLEM, STATUS_ROOM_IS_FULL, STATUS_USER_NOT_IN_ROOM, STATUS_USER_ALREADY_IN_ROOM, STATUS_FAILED }
        public const string SIGNUP_SUCCEEDED = "signup succeeded!";
        public const string LOGIN_SUCCEEDED = "login succeeded!";
        public const string DATA_BASE_PROBLEM = "dataBase problem.";
        public const string USER_EXIST = "user already exist.";
        public const string ROOM_IS_FULL = "the room is full.";
        public const string ROOM_DOESNT_EXIST = "the room doesnt seem to exist.";
        public const string JOINED_ROOM_SUCCEEDED = "joined room successfully!";
        public const string JOIN_ROOM_MORE_THAN_ONCE = "you cant join a room more than once.";
        public const string USER_DOESNT_EXIST = "user doesnt exist.";
        public const string PASSWORD_DOESNT_MATCH = "password doesnt match.";
        public const string USER_ALREADY_LOGGED = "user already logged in.";

        /*
        this function checks if the signed up action succeded or not
        input: none
        output: the status of the status of the request
        */
        static public string checkIfSigupSucceded()
        {
            SignupResponse SignupResponse = desirializer.deserializeRequest<SignupResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(MAX_DATA_SIZE)));
            switch (SignupResponse.status)
            {
                case (int)Status.STATUS_USER_EXIST:
                    {
                        return USER_EXIST;
                    }
                case (int)Status.STATUS_SUCCESS:
                    {
                        return SIGNUP_SUCCEEDED;
                    }
                case (int)Status.STATUS_DB_PROBLEM:
                    {
                        return DATA_BASE_PROBLEM;
                    }
            }
            return "";
        }

        /*
        this function checks if the user has joined a room succesfuly
        input: the id of the user
        output: the status of the request
        */
        static public string checkIfjoinRoomSucceeded(int id)
        {
            JoinRoomResponse response = desirializer.deserializeRequest<JoinRoomResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
            switch (response.status)
            {
                case (int)Status.STATUS_ROOM_IS_FULL:
                    return ROOM_IS_FULL;
                case (int)Status.STATUS_ROOM_DOESNT_EXIST:
                    return ROOM_DOESNT_EXIST;
                case (int)Status.STATUS_SUCCESS:
                    return JOINED_ROOM_SUCCEEDED;
                case (int)Status.STATUS_USER_ALREADY_IN_ROOM:
                    return JOIN_ROOM_MORE_THAN_ONCE;
            }
            return "";
        }
        /*
        this function checks if the login action succeded or not
        input: none
        output: the status of the request
        */
        static public string checkIfLoginSucceded()
        {
            loginResponse LoginResponse = desirializer.deserializeRequest<loginResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(MAX_DATA_SIZE)));
            switch (LoginResponse.status)
            {
                case (int)Status.STATUS_USER_DOESNT_EXIST:
                    {
                        return USER_DOESNT_EXIST;
                    }
                case (int)Status.STATUS_PASSWORD_DOESNT_MATCH:
                    {
                        return PASSWORD_DOESNT_MATCH;
                    }
                case (int)Status.STATUS_SUCCESS:
                    {
                        return LOGIN_SUCCEEDED;
                    }
                case (int)Status.STATUS_ALREADY_LOGGED_IN:
                    {
                        return USER_ALREADY_LOGGED;
                    }
                case (int)Status.STATUS_DB_PROBLEM:
                    {
                        return DATA_BASE_PROBLEM;
                    }
            }
            return "";
        }
        /*
        this function checks if the response if error
        input: none
        output: the message of the error, if there is no error than its an empty string
        */
        static public string checkIfErrorResponse()
        {
            string messageTypeCode = Communicator.GetMessageTypeCode();
            if (messageTypeCode == Convert.ToString(ERROR_RESPONSE))
            {
                ErrorResponse errorResponse = desirializer.deserializeRequest<ErrorResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(MAX_DATA_SIZE)));
                return errorResponse.message;
            }
            else
                return "";
        }
    }
}
