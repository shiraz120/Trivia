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
        static private string _LoginSuccededOrNotText;
        static public string LoginSuccededOrNot
        {
            get { return _LoginSuccededOrNotText; }
            set { _LoginSuccededOrNotText = value;}
        }
        static public void checkIfLoginSucceded()
        {
            Communicator.GetMessageTypeCode();
            string response = Communicator.GetStringPartFromSocket(Communicator.getSizePart(MAX_DATA_SIZE));
            loginResponse LoginResponse = desirializer.deserializeRequest<loginResponse>(response);
            switch(LoginResponse.status)
            {
                case 1:
                    {
                        LoginSuccededOrNot = "user doesnt exist.";
                        break;
                    }
            }
        }
    }
}
