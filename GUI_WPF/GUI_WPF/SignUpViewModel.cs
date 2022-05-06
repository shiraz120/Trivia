using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_WPF
{
    public class SignUpViewModel : INotifyDataErrorInfo
    {
        private readonly Dictionary<string, List<string>> _errorsForBindings = new Dictionary<string, List<string>>();
        private string _username;
        public string Username
        {
            get { return _username; }
            set
            {
                _username = value;
                if (string.IsNullOrWhiteSpace(_username))
                    AddError(nameof(_username), "Username must contain atleast 1 character.");
            }
        }
        public bool HasErrors => _errorsForBindings.Any();

        public event EventHandler<DataErrorsChangedEventArgs> ErrorsChanged;

        public IEnumerable GetErrors(string propertyName)
        {
            if(_errorsForBindings.ContainsKey(propertyName))
                return _errorsForBindings[propertyName];
            return null;
        }
        public void AddError(string propertyName, string errorMsg)
        {
            if(!_errorsForBindings.ContainsKey(propertyName))
                _errorsForBindings.Add(propertyName, new List<string>());
            _errorsForBindings[propertyName].Add(errorMsg);
            ErrorsChanged?.Invoke(this, new DataErrorsChangedEventArgs(propertyName));
        }
    }
}
