using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_WPF
{
    public class getQuestionResponse
    {
        public int status;
        public string question;
        public List<Tuple<int, string>> answers;
    }
}
