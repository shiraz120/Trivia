using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_WPF
{
    public class RoomData
    {
        public int id;
        public string name;
        public int maxPlayers;
        public int numOfQuestionsInGame;
        public int timePerQuestion;
        public int isActive;
    };
    public class GetRoomsResponse
    {
        public int status;
        public List<RoomData> rooms;
    }
}
