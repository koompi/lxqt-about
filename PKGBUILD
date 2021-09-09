pkgname=koompi-lxqt-about
pkgver=0.17.0
pkgrel=2
pkgdesc="LXQT about dialog."
arch=("x86_64")
groups=("lxqt")
provides=("lxqt-about")
conflicts=("lxqt-about")
license=("LGPL2.1")
depends=("liblxqt" "libQt5Xdg.so")
makedepends=("lxqt-build-tools" "tar" "gzip")
source=(
	"git+https://github.com/koompi/lxqt-about.git"
	"koompi.svg"
)
sha256sums=(
	'766ab60f907d4cfd37a630f66a4c381bab00a5bdcfae8b47d172148ae6601bf2'
	'50e4b89a439466067bb2a5eb3ba010c9cda8c10a64bdd57614556752c946aef8'
)

prepare(){
	cd "${srdir}"
	tar -xzvpf "$pkgver"-1.tar.gz -C .
}


build() {
	mkdir -p build
	cd build
	cmake "$srcdir/lxqt-about-$pkgver-1" \
		-DCMAKE_INSTALL_PREFIX=/usr
	make
}

package() {
	cd build
	make DESTDIR="$pkgdir" install

	install -D "${srcdir}/koompi.svg" "${pkgdir}/usr/share/icons/koompi.svg"
}