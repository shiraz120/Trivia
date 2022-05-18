using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_WPF
{
    public class createRoomRequest
    {
       public string roomName;
       public int maxUsers;
       public int questionCount;
       public int answerTimeout;
    }
    public class createRoomResponse
    {
        public int status;
    }
}
