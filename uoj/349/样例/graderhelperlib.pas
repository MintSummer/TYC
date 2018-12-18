unit graderhelperlib;
interface

function explore(x, y : longint) : longint;

procedure graderMain();

implementation

uses rts;

type Edge = record
	next : ^Edge;
	y : longint;
end;

var
	n, T, dataType : longint;
	firstEdge : array[0..300004] of ^Edge;
	edges : array[0..600009] of Edge;
	lastEdge : ^Edge = @edges[0];

procedure addEdge(u, v : longint);
begin
	inc(lastEdge);
	lastEdge^.next := firstEdge[u];
	lastEdge^.y := v;
	firstEdge[u] := lastEdge;
end;

var
	fa : array[0..300004] of longint;
	dTime, fTime : array[0..300004] of longint;
	dfsSeq : array[0..300004] of longint;

var
	childArrStart : array[0..300004] of ^longint;
	childArr : array[0..300004] of longint;

var
	stack : array[0..300004] of longint;

procedure dfs();
var
	top : longint = 1;
	nowTime : longint = 0;
	u, v, lastTop, i, j, tmp : longint;
	e : ^Edge;
begin
	stack[1] := 1;
	while top <> 0 do begin
		u := stack[top];
		if dTime[u] <> 0 then begin
			fTime[u] := nowTime;
			dec(top);
			continue;
		end;
		inc(nowTime);
		dTime[u] := nowTime;
		dfsSeq[nowTime] := u;
		lastTop := top;
		e := firstEdge[u];
		while e <> nil do begin
			v := e^.y;
			if v <> fa[u] then begin
				fa[v] := u;
				inc(top);
				stack[top] := v;
			end;
			e := e^.next;
		end;
		i := lastTop + 1;
		j := top;
		while i < j do begin
			tmp := stack[i];
			stack[i] := stack[j];
			stack[j] := tmp;
			inc(i);
			dec(j);
		end;
	end;
end;

var
	discovered : array[0..300004] of boolean;

procedure init();
var
	i, j, u, v : longint;
	childArrPointer : ^longint;
	e : ^Edge;
begin
	read(n, T, dataType);
	for i := 1 to n - 1 do begin
		read(u, v);
		addEdge(u, v);
		addEdge(v, u);
	end;
	fa[1] := 0;
	dfs();
	childArrPointer := @childArr[0];
	for i := 1 to n do begin
		childArrStart[i] := childArrPointer;
		e := firstEdge[i];
		while e <> nil do begin
			j := e^.y;
			if j <> fa[i] then begin
				childArrPointer^ := dTime[j];
				inc(childArrPointer);
			end;
			e := e^.next;
		end;
	end;
	childArrStart[n + 1] := childArrPointer;
	fillchar(discovered, sizeof(discovered), 0);
	discovered[1] := true;
end;

var
	cntExploreCalls : longint = 0;

function explore(x, y : longint) : longint;
var
	z, len, val, mid : longint;
	A : ^longint;
begin
	inc(cntExploreCalls);
	if cntExploreCalls > T then begin
		writeln('explore: too many calls');
		halt;
	end;
	if (x < 1) or (x > n) then begin
		writeln('explore: argument x (', x, ') not in [1, n]');
		halt;
	end;
	if (y < 1) or (y > n) then begin
		writeln('explore: argument y (', y, ') not in [1, n]');
		halt;
	end;
	if x = y then begin
		writeln('explore: argument x = y = ', x);
		halt;
	end;
	if not discovered[x] then begin
		writeln('explore: node x (', x, ') not discovered');
		halt;
	end;
	z := fa[x];
	if (dTime[x] < dTime[y]) and (fTime[x] >= fTime[y]) then begin
		A := childArrStart[x];
		len := childArrStart[x + 1] - A;
		val := dTime[y];
		while len > 1 do begin
			mid := len >> 1;
			if val < A[mid] then begin
				len := mid;
			end else begin
				A := A + mid;
				len := len - mid;
			end;
		end;
		z := dfsSeq[A[0]];
	end;
	discovered[z] := true;
	exit(z);
end;

procedure check();
var
	i : longint;
begin
	for i := 1 to n do begin
		if not discovered[i] then begin
			writeln('node ', i, ' not discovered after the game');
			halt;
		end;
	end;
	writeln('Correct');
	{$IFDEF DEBUG}
	writeln('# of explore calls = ', cntExploreCalls);
	{$ENDIF}
end;

procedure graderMain();
begin
	init();
	play(n, T, dataType);
	check();
end;

end.
