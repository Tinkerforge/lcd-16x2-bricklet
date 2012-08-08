program ExampleButtonCallbacks;

{$ifdef MSWINDOWS}{$apptype CONSOLE}{$endif}
{$ifdef FPC}{$mode OBJFPC}{$H+}{$endif}

uses
  SysUtils, IPConnection, BrickletLCD16x2;

type
  TExample = class
  private
    ipcon: TIPConnection;
    lcd: TBrickletLCD16x2;
  public
    procedure PressedCB(const i: byte);
    procedure ReleasedCB(const i: byte);
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = '6ko'; { Change to your UID }

var
  e: TExample;

{ Callback functions for button status }
procedure TExample.PressedCB(const i: byte);
begin
  WriteLn(Format('Pressed: %d', [i]));
end;

procedure TExample.ReleasedCB(const i: byte);
begin
  WriteLn(Format('Released: %d', [i]));
end;

procedure TExample.Execute;
begin
  { Create IP connection to brickd }
  ipcon := TIPConnection.Create(HOST, PORT);

  { Create device object }
  lcd := TBrickletLCD16x2.Create(UID);

  { Add device to IP connection }
  ipcon.AddDevice(lcd);
  { Don't use device before it is added to a connection }

  { Register button status callbacks to procedure PressedCB and ReleasedCB }
  lcd.OnButtonPressed := {$ifdef FPC}@{$endif}PressedCB;
  lcd.OnButtonReleased := {$ifdef FPC}@{$endif}ReleasedCB;

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy;
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
