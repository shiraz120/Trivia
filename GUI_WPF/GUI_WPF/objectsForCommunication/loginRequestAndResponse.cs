using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_WPF
{
    public class loginRequest
    {
        public string username { get; set; }
        public string password { get; set; }
    }
    public class loginResponse
    {
        public int status { get; set; }
    }
}
