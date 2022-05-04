using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_WPF
{
    public class RegistrationVM : IDataErrorInfo
    {
        static public bool IsDarkTheme { get; set; }
        private string _username;
        private bool _canSave;
        public bool CanSave
        {
            get { return _canSave; }
            set { _canSave = value; }
        }
        public string Error { get { return null; } }
        public string Username
        {
            get { return _username; }
            set
            {
                _username = value;
            }
        }
        public string this[string name]
        {
            get
            {
                string result = null;
                switch(name)
                {
                    case "Username":
                        if (string.IsNullOrWhiteSpace(Username))
                        {
                            result = "Username must be implemented";
                        }
                        break;
                }
                CanSave = result == null;
                return result;
            }
        }

    }
}
