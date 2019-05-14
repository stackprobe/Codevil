using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms;
using Charlotte.Tools;
using Charlotte.Common;

namespace Charlotte
{
	class Program
	{
		public const string APP_IDENT = "{6823e4bb-1fca-4236-857f-8fbd694521a9}";
		public const string APP_TITLE = "Donut2";

		static void Main(string[] args)
		{
			ProcMain.CUIMain(new Program().Main2, APP_IDENT, APP_TITLE);

			//Console.WriteLine("Press ENTER.");
			//Console.ReadLine();
		}

		private void Main2(ArgsReader ar)
		{
			DD.WinMain();
		}
	}
}
