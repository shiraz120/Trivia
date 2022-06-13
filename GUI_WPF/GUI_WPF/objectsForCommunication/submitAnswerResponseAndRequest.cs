using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_WPF
{
    public class submitAnswerResponse
    {
        public int status;
        public int correctAnswerId;
    }
    public class submitAnswerRequest
    {
        public int answerId;
    }
}
