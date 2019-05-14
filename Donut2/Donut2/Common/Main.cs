using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading;
using DxLibDLL;

namespace Charlotte.Common
{
	public partial class DD
	{
		private class Main
		{
			public static string GetVersionString()
			{
				return "0.00"; // TODO
			}

			public static Mutex ProcMtxHdl;
			public static int DxLibInited;

			public static void ReleaseProcMtxHdl()
			{
				ProcMtxHdl.ReleaseMutex();
				ProcMtxHdl.Dispose();
				ProcMtxHdl = null;
			}

			public static void PostSetScreenSize(int w, int h)
			{
				if (Gnd.MonitorRect.W == w && Gnd.MonitorRect.H == h)
				{
					//SetScreenPosition(Gnd.MonitorRect.L, Gnd.MonitorRect.T); // TODO
				}
			}
		}

		public static void WinMain()
		{
			DX.SetApplicationLogSaveDirectory(@"C:\tmp");

			//new Icon(@"C:\Dat\Icon\game_app.ico").Handle;

			new GameMain().Main();

			// TODO
		}
	}
}
