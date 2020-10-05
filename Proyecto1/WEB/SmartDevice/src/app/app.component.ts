import { Component, AfterViewInit, ElementRef } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent implements AfterViewInit{
  title = 'proyecto2';
  
  constructor(private elementRef: ElementRef){}
  ngAfterViewInit(){
        this.elementRef.nativeElement.ownerDocument.body.style.backgroundColor = '#5e5e5e';
  }
}
