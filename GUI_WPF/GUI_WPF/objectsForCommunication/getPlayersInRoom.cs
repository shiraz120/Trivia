using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_WPF
{
    public class GetPlayersInRoomRequest
    {
        public int roomId;
    }
    public class GetPlayersInRoomResponse
    {
        public List<string> players;
    }
}
