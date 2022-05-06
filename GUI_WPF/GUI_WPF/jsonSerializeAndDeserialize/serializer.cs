using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI_WPF
{
    public class serializer
    {
		const int MAX_BYTE_NUMBER = 256;
		const int MAX_DATA_LENGTH = 4;
		private static string addPaddingZeros(int length)
		{
			string sizeMsg = "";
			int counter = MAX_DATA_LENGTH - 1;
			string padded = "";
			while (length >= MAX_BYTE_NUMBER) // while length is bigger than 255 we add to sizeMsg the char of 255
			{
				sizeMsg += Convert.ToChar(MAX_BYTE_NUMBER);
				length -= MAX_BYTE_NUMBER;
				counter--;
			}
			sizeMsg += Convert.ToChar(length);
			padded = sizeMsg.PadLeft(MAX_DATA_LENGTH, '\0') + sizeMsg;
			return padded;
		}
		public static string serializeResponse<T>(T response, char code)
        {
			string data = JsonConvert.SerializeObject(response);
			string size = addPaddingZeros(data.Length);
			string check = code + size + data;
			return code + size + data;
        }
    }
}
