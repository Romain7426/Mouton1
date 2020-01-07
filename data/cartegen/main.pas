unit main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ComCtrls, ShellCtrls, FileCtrl;

type
  TForm1 = class(TForm)
    Label2: TLabel;
    lblSortie: TLabel;
    imgArf: TImage;
    imgOK: TImage;
    FileListBox: TFileListBox;
    cmdSauver: TButton;
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    TabSheet2: TTabSheet;
    RichEdit: TRichEdit;
    RichEditErreur: TRichEdit;
    procedure cmdGenererClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FileListBoxChange(Sender: TObject);
    procedure cmdSauverClick(Sender: TObject);
  private
    { Déclarations privées }
  public
    { Déclarations publiques }
  end;

var
  Form1: TForm1;
  entree: string;

  const NL = #13 + #10;

implementation

{$R *.dfm}

procedure TForm1.cmdGenererClick(Sender: TObject);
var e, s: TStringList;
    str: String;

    i, num: integer;
    quoi: string;
    estanime: string;
    nom_fich_image:string;
    bmp: TBitmap;
    c {compteur pour le parser}: integer;
    densite: single ;
    couleur: integer;

    ix, iy: integer;
begin
    bmp := TBitmap.Create;
    e := TStringList.Create;
    s := TStringList.Create;
    c := 0;
    num := 0;


    e.LoadFromFile('..\cartesplans\' + entree + '.carteplan');

    For i := 0 to e.Count-1 do
    Begin
        str := e.Strings[i];

        if str <> '' then
        Begin
            if str[1] = '%' then
            Begin
                str := Copy(str, 2, 20000);
                if c = 0 then
                     quoi := str
                else if c = 1 then
                      estanime := str
                else if c = 2 then
                     nom_fich_image := str
                else if c = 3 then
                     couleur := strtoint(str)
                else
                Begin
                     Val(str, densite, c);

                     if c <> 0 then
                         ShowMessage('arf!! ta densité c du kk.');

                     bmp.LoadFromFile('..\cartesplans\' + nom_fich_image);
                    for ix := 0 to bmp.Width-1 do
                         for iy := 0 to bmp.Height-1 do
                               if(bmp.Canvas.Pixels[ix, bmp.Height-1-iy] = couleur) then
                               if(Random(10000) / 100 <= densite) then
                               Begin
                                   s.Add('objet arbre' + inttostr(num) + ' {');
                                   s.Add('anime := ' + estanime + ';');
                                   s.Add('fichier := "' + quoi + '";');
                                   s.Add( 'position := {');
                                   s.Add( 'x := ' + inttostr(ix) + '.;');
                                   s.Add( 'y := ' + inttostr(iy) + '.;');
                                   s.Add( 'z := ' + inttostr(0) + '.;');
                                   s.Add( 'angle x := 0.;' );
                                   s.Add( 'angle y := 0.;');
                                   s.Add('angle z := 0.;');
                                   s.Add('};');
                                   s.Add('}');
                                   s.Add('');
                                   s.Add('');



                               End;

                               inc(num);

                                    { objet igloeo2 {
                            anime := faux;
                            fichier := "arbre01.nonanime";
                            position := {
                             x := 2.;
                             y := 6.;
                             z := 100.;
                             angle x := 0.;
                             angle y := 0.;
                             angle z := 0.;
                            }

                    c := -1;
                End;
                inc(c);
            End
            else
            Begin
            //str est une chaîne normale
               s.Add(str);
               c := 0;
            End;

        End;

    End;

    s.SaveToFile('..\cartes\' + entree + '.carte');
    imgOK.Visible := true;
imgArf.Visible := false;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
FileListBox.Directory := '../cartesplans';
end;

procedure TForm1.FileListBoxChange(Sender: TObject);
var path: string;
begin
entree := ExtractFileName(FileListBox.FileName);
path := ExtractFilePath(FileListBox.FileName);
entree := Copy(entree, 1, length(entree)-10);
lblSortie.caption := entree + '.carte';
imgOK.Visible := false;
imgArf.Visible := true;
if FileListBox.FileName <> '' then
RichEdit.Lines.LoadFromFile(FileListBox.FileName);
If FileExists(path + '..\cartes\' + entree + '.carte.carte.lexing.out') then
    RichEditErreur.Lines.LoadFromfile(path + '..\cartes\' + entree + '.carte.carte.lexing.out')
else
    RichEditErreur.Lines.Clear;

end;

procedure TForm1.cmdSauverClick(Sender: TObject);
begin
    RichEdit.PlainText := true;
    RichEdit.Lines.SaveToFile(FileListBox.FileName);
    cmdGenererClick(Sender);
end;

end.
