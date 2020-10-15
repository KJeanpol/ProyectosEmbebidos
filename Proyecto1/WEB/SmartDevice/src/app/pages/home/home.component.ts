import { Component, OnInit, ViewChild, ElementRef, OnDestroy } from '@angular/core';
import {ConnectionStatus,SubscriptionGrant} from '../../ngx-mqtt-client';
import {IClientOptions} from 'mqtt';
import { Subscription } from 'rxjs';
import { WebSocketService } from '../../../services/sockets/web-socket.service';
import { IMqttMessage, MqttService } from 'ngx-mqtt';
import { DomSanitizer, SafeResourceUrl } from '@angular/platform-browser';



export interface Foo {
    bar: string;
}

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent implements OnInit, OnDestroy {
    private subscription: Subscription;
    topicname: any;
    on:any="House/on";
    on1:any="House/on1";
    on2:any="House/on2";
    on3:any="House/on3";
    on4:any="House/on4";
    on5:any="House/on5";
    off:any="House/off";
    off1:any="House/off1";
    off2:any="House/off2";
    off3:any="House/off3";
    off4:any="House/off4";
    off5:any="House/off5";
    photo:any="photo";
    door:any="door";
    imagePath : SafeResourceUrl;
    msg: any;
    isConnected: boolean = false;
    @ViewChild('msglog', { static: true }) msglog: ElementRef;
  
    constructor(private _mqttService: MqttService, private socket:WebSocketService,
      private _sanitizer: DomSanitizer ) { }
  
    ngOnInit(): void {
      this.subscribeNewTopic();

    }
  
    ngOnDestroy(): void {
      this.subscription.unsubscribe();
    }
  
  
    subscribeNewTopic(): void {
      console.log('inside subscribe new topic')
      this.subscription = this._mqttService.observe(this.off).subscribe((message: IMqttMessage) => {
        this.msg = message;
        console.log('msg: ', message.payload.toString())
    //    this.logMsg('Message: ' + message.payload.toString() + '<br> for topic: ' + message.topic);
      //  this.imagePath = this._sanitizer.bypassSecurityTrustResourceUrl('data:image/jpg;base64,' 
         //        + this.msg.message.payload.toString().base64string);
      });

      this.subscription = this._mqttService.observe(this.on).subscribe((message: IMqttMessage) => {
        this.msg = message;
        console.log('msg: ', message.payload.toString())
     //   this.logMsg('Message: ' + message.payload.toString() + '<br> for topic: ' + message.topic);
       // this.imagePath = this._sanitizer.bypassSecurityTrustResourceUrl('data:image/jpg;base64,' 
           //      + this.msg.message.payload.toString().base64string);
      });

      this.subscription = this._mqttService.observe(this.door).subscribe((message: IMqttMessage) => {
        this.msg = message;
        console.log('msg: ', message.payload.toString())
        this.logMsg( message.payload.toString());
     //   this.logMsg('Message: ' + message.payload.toString() + '<br> for topic: ' + message.topic);
       // this.imagePath = this._sanitizer.bypassSecurityTrustResourceUrl('data:image/jpg;base64,' 
           //      + this.msg.message.payload.toString().base64string);
      });      

      this.subscription = this._mqttService.observe(this.photo).subscribe((message: IMqttMessage) => {
        this.msg = message;
        console.log('msg: ', message.payload.toString())
       // this.logMsg('Message: ' + message.payload.toString() + '<br> for topic: ' + message.topic);
        //this.imagePath=message.payload.toString()
        this.imagePath = this._sanitizer.bypassSecurityTrustResourceUrl('data:image/jpg;base64,' 
                 + this.msg.payload);

                 
      });

       }
  
    sendmsg(): void {
  
      //this.socket.emit("news","PRUEBAAA");
      //use unsafe publish for non-ssl websockets
      this._mqttService.unsafePublish(this.topicname, this.msg, { qos: 1, retain: true })
      this.msg = ''
    }
    On1(): void {
        this._mqttService.unsafePublish(this.on, "House/on1", { qos: 1, retain: true })
        this.msg = ''
      }
    On2(): void {
        this._mqttService.unsafePublish(this.on, "House/on2", { qos: 1, retain: true })
        this.msg = ''
      }

    On3(): void {
      this._mqttService.unsafePublish(this.on, "House/on3", { qos: 1, retain: true })
      this.msg = ''
      }


    On4(): void {
      this._mqttService.unsafePublish(this.on, "House/on4", { qos: 1, retain: true })
      this.msg = ''
      }

    On5(): void {
        this._mqttService.unsafePublish(this.on, "House/on5", { qos: 1, retain: true })
        this.msg = ''
      }
    
    Off1(): void {
        this._mqttService.unsafePublish(this.off, "House/off1", { qos: 1, retain: true })
        this.msg = ''
      }
    Off2(): void {
        this._mqttService.unsafePublish(this.off, "House/off2", { qos: 1, retain: true })
        this.msg = ''
      }

    Off3(): void {
      this._mqttService.unsafePublish(this.off, "House/off3", { qos: 1, retain: true })
      this.msg = ''
      }


    Off4(): void {
      this._mqttService.unsafePublish(this.off, "House/off4", { qos: 1, retain: true })
      this.msg = ''
      }

    Off5(): void {
        this._mqttService.unsafePublish(this.off, "House/off5", { qos: 1, retain: true })
        this.msg = ''
      } 
    TomarFoto(): void {
        this._mqttService.unsafePublish(this.photo, "photo", { qos: 1, retain: true })
        this.msg = ''
      } 
      
    Door(): void {
        this._mqttService.unsafePublish(this.door, "door", { qos: 1, retain: true })
        this.msg = ''
      }       
    logMsg(message): void {
      this.msglog.nativeElement.innerHTML += '<br><hr>' + message;
    }
  
    clear(): void {
      this.msglog.nativeElement.innerHTML = '';
    }
  }
  
  