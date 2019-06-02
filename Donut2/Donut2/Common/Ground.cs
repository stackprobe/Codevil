using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Charlotte.Common
{
	public partial class DD
	{
		private class Ground
		{
		}

		public class Gnd_t
		{
			// TODO
			//taskList* EL; // EffectList
			//int PrimaryPadId; // -1 == 未設定
			//SubScreen_t* MainScreen; // NULL == 不使用
			public IRect_t MonitorRect = new IRect_t();

			// app > @ Gnd_t

			// < app

			// SaveData {

			public int RealScreen_W;
			public int RealScreen_H;

			public int RealScreenDraw_L;
			public int RealScreenDraw_T;
			public int RealScreenDraw_W; // -1 == RealScreenDraw_LTWH 不使用
			public int RealScreenDraw_H;

			// TODO
		}

		public static Gnd_t Gnd = new Gnd_t();
	}
}
