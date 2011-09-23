/*************************************************************
 * This file was automatically generated on 2011-09-20.      *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

namespace Tinkerforge
{
	public class BrickletLCD16x2 : Device 
	{
		private static byte TYPE_WRITE_LINE = 1;
		private static byte TYPE_CLEAR_DISPLAY = 2;
		private static byte TYPE_BACKLIGHT_ON = 3;
		private static byte TYPE_BACKLIGHT_OFF = 4;
		private static byte TYPE_IS_BACKLIGHT_ON = 5;
		private static byte TYPE_SET_CONFIG = 6;
		private static byte TYPE_GET_CONFIG = 7;
		private static byte TYPE_IS_BUTTON_PRESSED = 8;
		private static byte TYPE_BUTTON_PRESSED = 9;
		private static byte TYPE_BUTTON_RELEASED = 10;

		public delegate void ButtonPressed(byte button);
		public delegate void ButtonReleased(byte button);

		public BrickletLCD16x2(string uid) : base(uid) 
		{
			messageCallbacks[TYPE_BUTTON_PRESSED] = new MessageCallback(CallbackButtonPressed);
			messageCallbacks[TYPE_BUTTON_RELEASED] = new MessageCallback(CallbackButtonReleased);
		}

		public void WriteLine(byte line, byte position, string text)
		{
			byte[] data = new byte[22];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_WRITE_LINE, 1, data);
			LEConverter.To((ushort)22, 2, data);
			LEConverter.To(line, 4, data);
			LEConverter.To(position, 5, data);
			LEConverter.To(text, 6, data);

			ipcon.Write(this, data, TYPE_WRITE_LINE, false);
		}

		public void ClearDisplay()
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_CLEAR_DISPLAY, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_CLEAR_DISPLAY, false);
		}

		public void BacklightOn()
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_BACKLIGHT_ON, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_BACKLIGHT_ON, false);
		}

		public void BacklightOff()
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_BACKLIGHT_OFF, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_BACKLIGHT_OFF, false);
		}

		public void IsBacklightOn(out bool backlight)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_IS_BACKLIGHT_ON, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_IS_BACKLIGHT_ON, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for IsBacklightOn in time");
			}

			backlight = LEConverter.BoolFrom(4, answer);

			writeEvent.Set();
		}

		public void SetConfig(bool cursor, bool blinking)
		{
			byte[] data = new byte[6];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_CONFIG, 1, data);
			LEConverter.To((ushort)6, 2, data);
			LEConverter.To(cursor, 4, data);
			LEConverter.To(blinking, 5, data);

			ipcon.Write(this, data, TYPE_SET_CONFIG, false);
		}

		public void GetConfig(out bool cursor, out bool blinking)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_CONFIG, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_CONFIG, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetConfig in time");
			}

			cursor = LEConverter.BoolFrom(4, answer);
			blinking = LEConverter.BoolFrom(5, answer);

			writeEvent.Set();
		}

		public void IsButtonPressed(byte button, out bool pressed)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_IS_BUTTON_PRESSED, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(button, 4, data);

			ipcon.Write(this, data, TYPE_IS_BUTTON_PRESSED, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for IsButtonPressed in time");
			}

			pressed = LEConverter.BoolFrom(4, answer);

			writeEvent.Set();
		}

		public int CallbackButtonPressed(byte[] data)
		{
			byte button = LEConverter.ByteFrom(4, data);

			((ButtonPressed)callbacks[TYPE_BUTTON_PRESSED])(button);
			return 5;
		}

		public int CallbackButtonReleased(byte[] data)
		{
			byte button = LEConverter.ByteFrom(4, data);

			((ButtonReleased)callbacks[TYPE_BUTTON_RELEASED])(button);
			return 5;
		}

		public void RegisterCallback(System.Delegate d)
		{
			if(d.GetType() == typeof(ButtonPressed))
			{
				callbacks[TYPE_BUTTON_PRESSED] = d;
			}
			else if(d.GetType() == typeof(ButtonReleased))
			{
				callbacks[TYPE_BUTTON_RELEASED] = d;
			}
		}
	}
}
