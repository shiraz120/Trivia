using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace GUI_WPF
{
    public class checkServerResponse
    {
        public const char ERROR_RESPONSE = 'c';
        public const int MAX_DATA_SIZE = 4;
        static public string checkIfErrorResponse()
        {
            if (Communicator.GetMessageTypeCode() == Convert.ToString(ERROR_RESPONSE))
            {
                ErrorResponse errorResponse = desirializer.deserializeRequest<ErrorResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(MAX_DATA_SIZE)));
                return errorResponse.message;
            }
            else
                return "";
        }
    }
}
