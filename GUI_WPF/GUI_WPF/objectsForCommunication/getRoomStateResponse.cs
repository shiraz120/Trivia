using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_WPF
{
    public class getRoomStateResponse
    {
        public int status;
        public bool hasGameBegun;
        public List<string> players;
        public int questionCount;
        public int answerTimeout;
    }
}
