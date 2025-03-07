/*
	Copyright (c) 2019, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.
	Please read that file and understand the license terms
	before using or altering the project.
*/

// The checking is NOT case sensitive

#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#include "core.h"
#include "icons.h"

// Default file icon is text file or normal link file
#define DEFAULT_FILE_ICON "󰈚"
#define DEFAULT_LINK_FILE_ICON ""
// Default directory icon is normal directory or normal link directory
#define DEFAULT_DIR_ICON  ""
#define DEFAULT_LINK_DIR_ICON ""


static const char * get_file_icon_by_ext( const char * ext, const bool is_link );
static const char * get_file_icon_by_name( const char * name, const bool is_link );

static bool find_in( const char * of, const char * values, bool is_exact_match );

#define IS( of, values ) find_in( of, values, true )
#define BEGINS( of, values ) find_in( of, values, false )

#define LOSSLESS_AUDIO "8svx, iff, aiff, aif, aifc, au, snd, bwf, wav, wave, cdda, raw, pcm, sam, ra, ram, flac, la, pac, ape, ofr, ofs, off, rka, shn, tak, tta, wv, brstm, dts, dtshd, dtsma, ast, aw, psf, alac, m4a"
#define LOSSY_AUDIO "amr, 3ga, mp1, mp2, mp3, spx, gsm, wma, aac, mpc, vqf, ots, swa, vox, voc, dwd, smp, ogg, oga, opus"
#define PLAYLIST "cue, aimppl, asx, xpl, xspf, zpl, m3u, m3u8, pls"

#define VIDEO "avi, flv, mkv, mov, mp4, ogv, webm"

static const bool is_default_icon( const char * icon )
{
	return strcmp( icon, DEFAULT_FILE_ICON ) == 0 || strcmp( icon, DEFAULT_LINK_FILE_ICON ) == 0;
}

const char * get_file_icon( const char * name, const char * ext, const bool is_link )
{
	const char * file_icon = get_file_icon_by_name( name, is_link );
	if( strcmp( ext, "\0" ) != 0 && is_default_icon( file_icon ) ) {
		const char * ext_icon = get_file_icon_by_ext( ext, is_link );
		return ext_icon;
	}
	return file_icon;
}

const char * get_dir_icon( const char * dir, const bool is_link )
{
	// if( BEGINS( dir, ".git, git" ) ) return "";
	// else if( BEGINS( dir, ".trash, trash" ) ) return "\uf1f8";
	// else if( BEGINS( dir, ".bash" ) ) return "\ue795";
	// else if( BEGINS( dir, ".bundle, .gem" ) ) return "\ue739";
	// else if( BEGINS( dir, ".cargo, .rustup" ) ) return "\ue7a8";
	// else if( BEGINS( dir, ".config" ) ) return "";
	// else if( BEGINS( dir, ".docker" ) ) return "\uf308";
	// else if( BEGINS( dir, ".go" ) ) return "\ue626";
	// else if( IS( dir, ".idea" ) ) return "\ue7b5";
	// else if( BEGINS( dir, ".mix" ) ) return "\ue62d";
	// else if( BEGINS( dir, ".npm, node_modules" ) ) return "\ue5fa";
	// else if( BEGINS( dir, ".vs, .vscode" ) ) return "\ue70c";
	// else if( BEGINS( dir, ".weechat" ) ) return "\ufbee";
	// else if( BEGINS( dir, "application" ) ) return "";
	// else if( BEGINS( dir, "bin, config" ) ) return "\ue5fc";
	// else if( BEGINS( dir, "desktop" ) ) return "";
	// else if( BEGINS( dir, "download" ) ) return "\uf74c";
	// else if( BEGINS( dir, "library" ) ) return "\uf830";
	// else if( BEGINS( dir, "movie" ) ) return "\uf880";
	// else if( BEGINS( dir, "music, songs, audio" ) ) return "\uf832";
	// else if( BEGINS( dir, "photo, picture" ) ) return "\uf03e";
	// else if( IS( dir, "__pycache__" ) ) return "\uf81f";
	// else if( BEGINS( dir, "video" ) ) return "\uf03d";

	if( is_link ) return DEFAULT_LINK_DIR_ICON;
	return DEFAULT_DIR_ICON;
}

static const char * get_file_icon_by_ext( const char * ext, const bool is_link )
{
	// OS

	// Apple
	if( IS( ext, "DS_Store" ) ) return "";

	// Configuration

	else if( IS( ext, "json" ) ) return "";
	else if( IS( ext, "lock" ) ) return "";
	else if( IS( ext, "ini, yaml, yml, env, toml" ) ) return "";

	// Data handling / manipulation

	else if( IS( ext, "html" ) ) return "";
	else if( IS( ext, "md" ) ) return "";
	else if( IS( ext, "xml, ui" ) ) return "󰗀";

	// Git

	else if( BEGINS( ext, "git" ) ) return "";

	// Terminal stuff

	else if( IS( ext, "zsh, bash, sh" ) ) return "";
	else if( BEGINS( ext, "zsh, bash" ) ) return "";
	else if( BEGINS( ext, "vim" ) ) return "";

	// Databases
	else if( IS( ext, "sql, sqlite" ) ) return "";

	// Audio
	// lossless
	else if( IS( ext, LOSSLESS_AUDIO ) ) return "\uf001";
	//lossy
	else if ( IS( ext, LOSSY_AUDIO ) ) return "\ufc58";
	// playlist
	else if ( IS ( ext, PLAYLIST ) ) return "\uf910";
	
	// Video
	else if ( IS( ext, VIDEO ) ) return "";
	// Languages

	// C, C++
	else if( IS( ext, "h, hh,hpp,hxx, h++" ) ) return "";
	else if( IS( ext, "c" ) ) return "";
	else if( IS( ext, "cc, cpp, cxx, c++" ) ) return "";
	// C#
	else if( IS( ext, "cs" ) ) return "󰌛";
	// Closure
	else if( IS( ext, "clj, cljs, cljc, edn" ) ) return "";
	// Coffeescript
	else if( IS( ext, "coffee, litcoffee" ) ) return "";
	// Elixir
	else if( IS( ext, "ex, exs, eex" ) ) return "";
	// Elm
	else if( IS( ext, "elm" ) ) return "";
	// Erlang
	else if( IS( ext, "erl, hrl" ) ) return "\ue7b1";
	// F-Sharp
	else if( IS( ext, "fs, fsi, fsscript" ) ) return "";
	// Go
	else if( IS( ext, "go" ) ) return "";
	// Haskell
	else if( IS( ext, "hs, lhs" ) ) return "";
	// Java
	else if( IS( ext, "java, class, jar" ) ) return "";
	// JS
	else if( IS( ext, "js" ) ) return "󰌞";
	// Julia
	else if( IS( ext, "jl" ) ) return "";
	// Lua
	else if( IS( ext, "lua" ) ) return "";
	// Perl
	else if( IS( ext, "pl, pm, t, pod" ) ) return "";
	// Prolog
	else if( IS( ext, "pro, P" ) ) return "";
	// Python
	else if( IS( ext, "py, pyc, pyd, pyx" ) ) return "";
	// Ruby
	else if( IS( ext, "rb" ) ) return "";
	// Rust
	else if( IS( ext, "rs, rlib" ) ) return "";
	// Scala
	else if( IS( ext, "scala, sc" ) ) return "";
	// Switft
	else if( IS( ext, "swift" ) ) return "";
	// Typescript
	else if( IS( ext, "ts, tsx" ) ) return "";

	if( is_link ) return DEFAULT_LINK_FILE_ICON;
	return DEFAULT_FILE_ICON;
}

static const char * get_file_icon_by_name( const char * name, const bool is_link )
{
	// Development
	if( BEGINS( name, "Makefile" ) ) return "";
	else if( BEGINS( name, "Dockerfile, docker-compose" ) ) return "󰡨";

	// Other
	if( BEGINS( name, "LICENSE, license, copying, COPYING" ) ) return "";
	// TODO:
	if( is_link ) return DEFAULT_LINK_FILE_ICON;
	return DEFAULT_FILE_ICON;
}

static inline bool is_whitespc( const char c ) { return c == ',' || c == ' ' || c == '\0'; }

static bool find_in( const char * of, const char * values, bool is_exact_match )
{
	int len_val = strlen( values );
	char tmp_str[ 100 ];
	int tmp_ctr = 0;
	for( int i = 0; i <= len_val; ++i ) {
		if( is_whitespc( values[ i ] ) ) {
			if( tmp_ctr == 0 ) continue;
			tmp_str[ tmp_ctr ] = '\0';
			if( is_exact_match ) {
				if( strcasecmp( of, tmp_str ) == 0 ) return true;
			}
			else {
				if( strncasecmp( of, tmp_str, strlen( tmp_str ) ) == 0 ) return true;
			}
			strcpy( tmp_str, "\0" );
			tmp_ctr = 0;
			continue;
		}
		tmp_str[ tmp_ctr++ ] = values[ i ];
	}
	return false;
}
