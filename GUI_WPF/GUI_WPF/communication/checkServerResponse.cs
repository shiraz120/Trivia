using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace GUI_WPF
{
    public class checkServerResponse
    {
        public enum Status { STATUS_USER_DOESNT_EXIST = 1, STATUS_USER_EXIST, STATUS_PASSWORD_DOESNT_MATCH, STATUS_SUCCESS, STATUS_ALREADY_LOGGED_IN, STATUS_DOESNT_LOGGED_IN, STATUS_NO_ROOMS, STATUS_NO_USERS_LOGGED_IN, STATUS_ROOM_DOESNT_EXIST, STATUS_DB_PROBLEM, STATUS_ROOM_IS_FULL }
        public const int MAX_DATA_SIZE = 4;
        public const string SIGNUP_SUCCEEDED = "signup succeeded!";
        public const string LOGIN_SUCCEEDED = "login succeeded!";
        public const string DATA_BASE_PROBLEM = "dataBase problem.";
        public const string ROOM_IS_FULL = "the room is full.";
        public const string ROOM_DOESNT_EXIST = "the room doesnt seem to exist.";
        public const string JOINED_ROOM_SUCCEEDED = "joined room successfully!";
        
        static public string checkIfSigupSucceded()
        {
            Communicator.GetMessageTypeCode();
            SignupResponse SignupResponse = desirializer.deserializeRequest<SignupResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(MAX_DATA_SIZE)));
            switch (SignupResponse.status)
            {
                case (int) Status.STATUS_USER_EXIST:
                    {
                        return "user already exist.";
                    }
                case (int) Status.STATUS_SUCCESS:
                    {
                        return SIGNUP_SUCCEEDED;
                    }
                case (int) Status.STATUS_DB_PROBLEM:
                    {
                        return DATA_BASE_PROBLEM;
                    }
            }
            return "";
        }
        static public string checkIfjoinRoomSucceeded(int id)
        {
            Communicator.GetMessageTypeCode();
            JoinRoomResponse response = desirializer.deserializeRequest<JoinRoomResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
            switch(response.status)
            {
                case (int)Status.STATUS_ROOM_IS_FULL:
                    return ROOM_IS_FULL;
                case (int)Status.STATUS_ROOM_DOESNT_EXIST:
                    return ROOM_DOESNT_EXIST;
                case (int)Status.STATUS_SUCCESS:
                        return JOINED_ROOM_SUCCEEDED;
            }
            return "";
        }
        static public int checkIfLogoutSucceeded()
        {
            Communicator.GetMessageTypeCode();
            logoutResponse logoutResponse = desirializer.deserializeRequest<logoutResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(MAX_DATA_SIZE)));
            return logoutResponse.status;
        }
        static public string checkIfLoginSucceded()
        {
            Communicator.GetMessageTypeCode();
            loginResponse LoginResponse = desirializer.deserializeRequest<loginResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(MAX_DATA_SIZE)));
            switch(LoginResponse.status)
            {
                case (int)Status.STATUS_USER_DOESNT_EXIST:
                    {
                        return "user doesnt exist.";
                    }
                case (int)Status.STATUS_PASSWORD_DOESNT_MATCH:
                    {
                        return "password doesnt match.";
                    }
                case (int)Status.STATUS_SUCCESS:
                    {
                        return  LOGIN_SUCCEEDED;
                    }
                case (int)Status.STATUS_ALREADY_LOGGED_IN:
                    {
                        return "user already logged in.";
                    }
                case (int)Status.STATUS_DB_PROBLEM:
                    {
                        return DATA_BASE_PROBLEM;
                    }
            }
            return "";
        }
    }
}
