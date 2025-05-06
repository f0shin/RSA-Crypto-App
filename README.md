# RSA-Crypto-App

## 目次

- [プロジェクト概要](#プロジェクト概要)
- [技術スタック](#技術スタック)
- [開発環境](#開発環境)
- [主要機能](#主要機能)
- [設計概要](#設計概要)
- [学んだこと](#学んだこと)
- [改善点](#改善点)

<br>

## プロジェクト概要

CとOpenSSL、Win32APIを活用したRSA暗号化プログラムの開発<br>
<br>

## 技術スタック

#C, #OpenSSL, #RSA, #Win32_API<br>
<br>

## 開発環境

✅ 言語 : C<br>
✅ OS : Windows<br>
✅ IDE : CodeBlock<br>
✅ コンパイラ : GCC(MinGW)<br>
<br>

## 主要機能

✅ RSA暗号化・復号化<br>
✅ Win32 APIによるGUI開発<br>
✅ ファイル処理 - ファイルの読み取り及び書き込み、フォルダの自動生成など<br>
<br>

## 設計概要

✅ 暗号化ステップ<br>
<table border="1">
<tr>
<td>任意のテキスト ファイルを読み込む。</td>
</tr>
<tr>
<td style="text-align:center;">⬇️</td>
</tr>
<tr>
<td>📝RSA 暗号化:<br>
1) プライベート鍵ファイル(private.pem)と共有鍵ファイル(public.pem)の自動生成する。<br>
2) 共有キーファイル(public.pem)で暗号化した後、<br>
3) 暗号化されたファイル(encrypted.bat)を生成する。</td>
</tr>
</table>

<br>

✅ 復号化ステップ<br>
<table border="1">
<tr>
<td>プライベート鍵ファイル(private.pem)と暗号化されたファイル(encrypted.bat)を読み込む。</td>
</tr>
<tr>
<td style="text-align:center;">⬇️</td>
</tr>
<tr>
<td>📝RSA復号化 : <br>
1) プライベート鍵ファイル(private.pem)で復号化した後、<br>
2) 元のテキストファイル(decrypted.txt)を生成する。<br>
</td>
</tr>
</table>
<br>

## 学んだこと

✅ 暗号アルゴリズムについての知識<br>
✅ ファイルシステムについての知識<br>
✅ C言語によるGUI開発の知識<br>
<br>

## 改善点

😥 UTF-8ファイル処理問題 - UTF-8エンコーディングを完璧に処理できず、<br>
RSA暗号化及び復号化過程でテキストファイルを正しく読み書きする時に壊れる問題が発生する。<br>
😊Windows APIのWideChar及びCreateFileW()(fopen()代替)、別にBase64を積極的に活用する方法を考案中。<br>

<br>
<br>

## 목차

- [프로젝트 개요](#프로젝트-개요)
- [기술 스택](#기술-스택)
- [개발 환경](#개발-환경)
- [주요 기능](#주요-기능)
- [설계 개요](#설계-개요)
- [배운 점](#배운-점)
- [아쉬운 점 및 개선 방안](#아쉬운-점-및-개선-방안)

<br>

## 프로젝트 개요

C와 OpenSSL, Win32 API를 활용한 RSA 암호화 프로그램 개발<br>
<br>

## 기술 스택

#C, #OpenSSL, #RSA, #Win32_API<br>
<br>

## 개발 환경

✅ 언어: C<br>
✅ OS: Windows<br>
✅ IDE: CodeBlock<br>
✅ 컴파일러: GCC (MinGW)<br>
<br>

## 주요 기능

✅ RSA 암호화/복호화<br>
✅ Win32 API를 통한 GUI 개발<br>
✅ 파일 처리 - 파일 읽기/쓰기, 폴더 자동 생성 등<br>
<br>

## 설계 개요

✅ 암호화 단계
<table border="1">
<tr>
<td>사용자가 임의의 text 파일을 불러옴.</td>
</tr>
<tr>
<td style="text-align:center;">⬇️</td>
</tr>
<tr>
<td>📝RSA 암호화 :<br>
1) 개인 키 파일(private.pem)와 공유 키 파일(public.pem) 자동 생성함.<br>
2) 공유 키 파일(public.pem)로 암호화 후, <br>
3) 암호화된 파일(encrypted.bat) 생성함.</td>
</tr>
</table>

<br>

✅ 복호화 단계
<table border="1">
<tr>
<td>사용자가 개인 키 파일(private.pem)와 암호화된 파일(encrypted.bat)을 불러옴.</td>
</tr>
<tr>
<td style="text-align:center;">⬇️</td>
</tr>
<tr>
<td>📝RSA 복호화 :<br>
1) 개인 키 파일(private.pem)로 복호화 후, <br>
2) 원본 텍스트파일(decrypted.txt) 생성함.</td>
</tr>
</table>
<br>

## 배운 점

✅ 암호 알고리즘에 대한 지식<br>
✅ 파일 시스템에 대한 지식<br>
✅ C언어를 통한 GUI 개발 지식<br>
<br>

## 아쉬운 점 및 개선 방안

😥 UTF-8 파일 처리 문제 - UTF-8 인코딩을 완벽하게 처리하지 못하여, <br>
RSA 암호화 및 복호화 과정에서 텍스트 파일을 올바르게 읽고 쓸 때 깨지는 문제가 발생함.<br>
😊 Windows API의 WideChar 및 CreateFileW() (fopen() 대체), 별개로 Base64를 적극 활용하는 방법을 고안 중임.<br>
<br>
