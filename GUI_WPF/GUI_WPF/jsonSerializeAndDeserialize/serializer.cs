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
		/*
		this function adds padding to the length
		input: the length
		output: the padded string
		*/
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
			padded = sizeMsg.PadLeft(MAX_DATA_LENGTH, '\0');
			return padded;
		}
		
		/*
		this function serialize the response so that it will be ready to send to the server
		input: the response and the code
		output: the response
		*/
		public static string serializeResponse<T>(T response, char code)
        {
			string data = JsonConvert.SerializeObject(response);
			string size = addPaddingZeros(data.Length);
			return code + size + data;
        }
    }
}
