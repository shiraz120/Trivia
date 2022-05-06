using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_WPF
{
    public class desirializer
    {
        public static T deserializeRequest<T>(string buffer)
        {
            T jsonFromData = JsonConvert.DeserializeObject<T>(buffer);
            return jsonFromData;
        }
    }
}
