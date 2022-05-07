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
        public enum Status { STATUS_USER_DOESNT_EXIST = 1, STATUS_USER_EXIST, STATUS_PASSWORD_DOESNT_MATCH, STATUS_SUCCESS, STATUS_ALREADY_LOGGED_IN, STATUS_DOESNT_LOGGED_IN, STATUS_COULDNT_RECEIVE_USER_STATS, STATUS_NO_ROOMS, STATUS_NO_USERS_LOGGED_IN, STATUS_ROOM_DOESNT_EXIST, STATUS_DB_PROBLEM }
        const int MAX_DATA_SIZE = 4;
        static public string checkIfSigupSucceded()
        {
            Communicator.GetMessageTypeCode();
            string response = Communicator.GetStringPartFromSocket(Communicator.getSizePart(MAX_DATA_SIZE));
            SignupResponse SignupResponse = desirializer.deserializeRequest<SignupResponse>(response);
            switch (SignupResponse.status)
            {
                case 2:
                    {
                        return "user already exist.";
                    }
                case 4:
                    {
                        return "signup succeeded!";
                    }
                case 11:
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
                case 1:
                    {
                        return "user doesnt exist.";
                    }
                case 3:
                    {
                        return "password doesnt match.";
                    }
                case 4:
                    {
                        return  "login succeeded!";
                    }
                case 5:
                    {
                        return "user already logged in.";
                    }
                case 11:
                    {
                        return "dataBase problem.";
                    }
            }
            return "";
        }
    }
}
