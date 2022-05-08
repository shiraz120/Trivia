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
        enum Status { STATUS_USER_DOESNT_EXIST = 1, STATUS_USER_EXIST, STATUS_PASSWORD_DOESNT_MATCH, STATUS_SUCCESS, STATUS_ALREADY_LOGGED_IN, STATUS_DOESNT_LOGGED_IN, STATUS_COULDNT_RECEIVE_USER_STATS, STATUS_NO_ROOMS, STATUS_NO_USERS_LOGGED_IN, STATUS_ROOM_DOESNT_EXIST, STATUS_DB_PROBLEM, STATUS_ROOM_IS_FULL }
        const int MAX_DATA_SIZE = 4;
        public const string SIGNUP_SUCCEEDED = "signup succeeded!";
        public const string LOGIN_SUCCEEDED = "login succeeded!";
        static public string checkIfSigupSucceded()
        {
            Communicator.GetMessageTypeCode();
            string response = Communicator.GetStringPartFromSocket(Communicator.getSizePart(MAX_DATA_SIZE));
            SignupResponse SignupResponse = desirializer.deserializeRequest<SignupResponse>(response);
            switch (SignupResponse.status)
            {
                case (int) Status.STATUS_USER_EXIST:
                    {
                        return "user already exist.";
                    }
                case (int)Status.STATUS_SUCCESS:
                    {
                        return SIGNUP_SUCCEEDED;
                    }
                case (int)Status.STATUS_DB_PROBLEM:
                    {
                        return "dataBase problem.";
                    }
            }
            return "";
        }
        static public int checkIfLogoutSucceeded()
        {
            Communicator.GetMessageTypeCode();
            string response = Communicator.GetStringPartFromSocket(Communicator.getSizePart(MAX_DATA_SIZE));
            logoutResponse logoutResponse = desirializer.deserializeRequest<logoutResponse>(response);
            return logoutResponse.status;
        }
        static public string checkIfLoginSucceded()
        {
            Communicator.GetMessageTypeCode();
            string response = Communicator.GetStringPartFromSocket(Communicator.getSizePart(MAX_DATA_SIZE));
            loginResponse LoginResponse = desirializer.deserializeRequest<loginResponse>(response);
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
                        return "dataBase problem.";
                    }
            }
            return "";
        }
    }
}
